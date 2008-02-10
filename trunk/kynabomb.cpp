#include "kynabomb.h"
#include "kynafield.h"
#include "kynalevel.h"
#include "kynaplayer.h"
#include <iostream>

KynaBomb::KynaBomb ( boxI x, boxI y,KynaUnit *unit, KynaLevel *level,int ticks,KynaTileset *tileset )
{

//  	qDebug() << unit->getName() << " place bomb" << unit->bombs.size();
	range = unit->getBuff ( BUFF_BOMB_RANGE );
	this->level = level;
	this->ticks = ticks;
	this->tileset = tileset;

	this->unit = unit;

	mode = MODE_BOMB_DONOTHING;
	explodeTimer = new QTimer();
	connect ( explodeTimer,SIGNAL ( timeout() ),this,SLOT ( tick() ) );

	this->x = x;
	this->y = y;

}

void KynaBomb::start()
{
	if ( !explodeTimer->isActive() )
	{
		qDebug() << "Bomb start";
		item = new KynaPixmapItem ( tileset );
		QList<QString> *list = new QList<QString>;
		list->append ( "bomb.png" );
		item->setAnimations ( list,0 );
		item->start ( 0 );
		level->addItem ( item );
		item->setZValue ( ZINDEX_BOMB + 2 );

		item->setOffset ( x*BOX_LENGTH*PX_MULTI,y*BOX_LENGTH*PX_MULTI );
		mode = MODE_BOMB_TICKS;
		explodeTimer->start ( 20 );
	}
}

void KynaBomb::animateFire()
{
	if ( firetime > 0 )
	{
		firetime--;
		explodeTimer->start ( 20 );
	}
	else
	{

		for ( int i = 0; i < fields.size() ; i++ )
		{
			fields[i]->removeFired ( this );
		}
		destroy();
	}
}

void KynaBomb::destroy()
{

	for ( int i = 0; i < fireList.size(); i++ )
	{
		delete fireList[i];
	}

//TODO is that good?
	delete item;
	delete this;
}

void KynaBomb::fireDirection ( boxI modX, boxI modY )
{
	KynaField *field;

	int range = this->range;

	for ( int i = 1; i <= range; i++ )
	{
		field = level->getField ( x + modX * i, y + modY * i );

		if ( field->fire ( this ) == FIRE_WAY_STOP )
			return;

		fields.append ( field );

		QList<QString> list;

		KynaPixmapItem *tempPixmapItem = new KynaPixmapItem ( tileset );
		if ( i != range )
		{
			if ( modY == 0 )
				list.append ( "explode_h.png" );
			else
				list.append ( "explode_v.png" );
			tempPixmapItem->setZValue ( ZINDEX_BOMB+1 );
		}
		else
		{
			if ( modY == 0 && modX < 0 )
				list.append ( "explode_el.png" );
			else if ( modY == 0 && modX > 0 )
				list.append ( "explode_er.png" );
			else if ( modY < 0 && modX == 0 )
				list.append ( "explode_et.png" );
			else if ( modY > 0 && modX == 0 )
				list.append ( "explode_eb.png" );
				tempPixmapItem->setZValue ( ZINDEX_BOMB );
		}


		tempPixmapItem->stop();
		tempPixmapItem->setAnimations ( &list,0 );
		tempPixmapItem->start ( 0 );

		tempPixmapItem->setOffset ( ( x + modX * i ) * BOX_LENGTH, ( y + ( modY * i ) ) * BOX_LENGTH );


		level->addItem ( tempPixmapItem );
		fireList.append ( tempPixmapItem );

	}
}

void KynaBomb::explode()
{
	if ( mode == MODE_BOMB_EXPLODED )
		return;

	mode = MODE_BOMB_EXPLODED;

	disconnect ( explodeTimer, 0, 0, 0 );
	connect ( explodeTimer,SIGNAL ( timeout() ),this,SLOT ( animateFire() ) );

	firetime = BOMB_FIRE_TIME;

	QList<QString> list;
	list.append ( "explode_c.png" );
	item->stop();
	item->setAnimations ( &list,0 );
	item->start ( 0 );

	fireDirection ( 0,  1 ) ;
	fireDirection ( 0, -1 );
	fireDirection ( 1,  0 );
	fireDirection ( -1,  0 );

	unit->bombIsDone ( this );
	KynaField *field = level->getField ( x,y );
	field->removeBomb ( this );
	field->fire ( this );
	fields.append ( field );
	animateFire();

}


void KynaBomb::tick()
{
	if ( ticks > 0 )
	{
		ticks--;

	}
	else
	{
		explodeTimer->stop();
		explode();
		return;
	}


}

KynaBomb::~ KynaBomb()
{
// 	delete item;
	explodeTimer->stop();
}


