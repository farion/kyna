#include <iostream>

#include "kynaunit.h"
#include "kynalevel.h"


KynaUnit::KynaUnit()
{

}

KynaUnit::KynaUnit ( KynaLevel *level, KynaTileset *tileset, UnitSettings *settings )
{
	//verteile Settings

	this->x = settings->startX*BOX_LENGTH+BOX_LENGTH/2;
	this->y = settings->startY*BOX_LENGTH+BOX_LENGTH/2;
	this->level = level;
	this->view = NULL;
	this->settings = settings;

	this->tileset = tileset;

	this->movex = 0;
	this->movey = 0;
	this->lastx = 0;
	this->lasty = 0;
	control = NULL;

	item = new KynaPixmapItem ( tileset );


	item->setAnimations ( settings->downtiles,0 );
	item->start ( 0 );

	addBuff ( BUFF_BOMB_COUNT, 3 );
	addBuff ( BUFF_BOMB_RANGE, 3 );
}


/**
 * @brief is called, if unit enters a field with other units on it or if other units enter the field of unit
 * @todo implement me
 * @param unit
 */
void KynaUnit::meet ( KynaUnit *unit )
{
	//Dead units can not kill someone
	if(isDead() || unit->isDead())
		return;

	if(getType()  == UNIT_TYPE_PLAYER && unit->getType() == UNIT_TYPE_ENEMY )
		dieNow();
	else if (getType()  == UNIT_TYPE_ENEMY && unit->getType() == UNIT_TYPE_PLAYER )
		unit->dieNow();
	
}


void KynaUnit::fire()
{
	dieNow();
}



/**
 * @brief The unit gets bounded to the given view, the view will center on this unit
 * @param view QGraphicsView, if NULL, the unit leave the MainUnitMode
 */
void KynaUnit::setAsMainUnitFor ( QGraphicsView *view )
{

	if ( view == NULL )
	{
		this->view = NULL;
	}
	else
	{
		this->view = view;
		view->centerOn ( item );
	}
}


void KynaUnit::setName ( QString name )
{
	settings->name = name;
}

QString KynaUnit::getName()
{
	return settings->name;
}

bool KynaUnit::addBuff ( int buffType,int value )
{

	/* Check if buff is there */
	for ( int i=0; i < buffs.size(); i++ )
	{
		if ( buffs[i]->getType() == buffType )
		{
			buffs[i]->setValue ( value );
			return true;
		}
	}

	buffs.append ( new KynaBuff ( buffType, value, this ) );

	return true;
}


bool KynaUnit::removeBuff ( int buffType )
{
	for ( int i=0; i < buffs.size(); i++ )
	{
		if ( buffs[i]->getType() == buffType )
		{
			buffs.removeAt ( i );
			return true;
		}
	}

	return false;
}

int KynaUnit::getBuff ( int buffType )
{
	for ( int i=0; i < buffs.size(); i++ )
	{
		if ( buffs[i]->getType() == buffType )
		{
			return buffs[i]->getValue();
		}
	}

	return -1;
}

void KynaUnit::placeOnLevel()
{
	int x,y;

	x = ( this->x- ( UNIT_LENGTH/2 ) ) *PX_MULTI;
	y = ( this->y- ( UNIT_LENGTH/2 ) ) *PX_MULTI;

//TODO set Animation
// 	item->setPixmap ( tileset[tile] );
	level->addItem ( item );
	switch ( settings->type )
	{
		case UNIT_TYPE_PLAYER:
			item->setZValue ( ZINDEX_PLAYER );
			break;
		default:

			item->setZValue ( ZINDEX_KI );
			break;
	}
	item->setOffset ( x,y );

}

//TODO used
void KynaUnit::setTileset ( QPixmap *tileset )
{
// 	this->tileset = tileset;
	//TODO
// 	item->setPixmap ( tileset[tile] );

}


void KynaUnit::bombIsDone ( KynaBomb *bomb )
{
	for ( int i = 0; i < bombs.size() ; i++ )
	{
		if ( bomb == bombs[i] )
		{
			bombs.removeAt ( i );
			return;
		}
	}
}

bool KynaUnit::placeBomb()
{

	KynaField *field = level->getField ( getBoxX(),getBoxY() );

	if ( getBuff ( BUFF_BOMB_COUNT ) > bombs.size() )
	{
		KynaBomb *bomb = new KynaBomb ( getBoxX(),getBoxY(),this,level,100,tileset );
		if ( field->placeBomb ( bomb ) )
		{
			bombs.append ( bomb );
			return true;
		}
		else
		{
			delete bomb;
			return false;
		}
	}
	else
	{
		return false;
	}
}



bool KynaUnit::moveRight ( bool direct )
{
	boxI x = ( boxI ) ceil ( this->x / BOX_LENGTH );
	boxI y = ( boxI ) ceil ( this->y / BOX_LENGTH );
	KynaField *field_old;
	KynaField *field;
	int pos = this->x % BOX_LENGTH;
	int halflength = BOX_LENGTH/2;

	if ( direct && lastx!=1){
		item->setAnimations ( settings->righttiles,200 );
		item->start ( -1 );
		lastx=1;
		lasty=0;
	}


	field = level->getField ( x+1,y );

	if ( pos < halflength || field->unitKnocking ( this ) )
	{
		this->x += settings->movespeed;

		if ( x != ( boxI ) ceil ( this->x / BOX_LENGTH ) || y != ( boxI ) ceil ( this->y / BOX_LENGTH ) )
		{
			field_old = level->getField ( x,y );
			field_old->unitLeave ( this );
			field->unitEnter ( this );
		}

		if ( this->y % BOX_LENGTH < halflength )
		{
			if ( movey>=0 )
			{
				if ( direct ) movey=0;
				if ( direct ) moveDown ( false );
			}
		}
		else if ( this->y % BOX_LENGTH > halflength )
		{
			if ( movey<=0 )
			{
				if ( direct ) movey=0;
				if ( direct ) moveUp ( false );
			}
		}
		return true;
	}
	else
	{
		if ( this->y % BOX_LENGTH < halflength )
		{
			field = level->getField ( x+1,y-1 );
			if ( field->unitKnocking ( this ) )
			{
				if ( movey<=0 )
				{
					if ( direct ) movey=0;
					if ( direct ) moveUp ( false );
				}
			}
		}
		else if ( this->y % BOX_LENGTH > halflength )
		{
			field = level->getField ( x+1,y+1 );
			if ( field->unitKnocking ( this ) )
			{
				if ( movey>=0 )
				{
					if ( direct ) movey=0;
					if ( direct ) moveDown ( false );
				}
			}
		}
		return false;
	}
}

bool KynaUnit::moveLeft ( bool direct )
{
	boxI x = ( boxI ) ceil ( this->x / BOX_LENGTH );
	boxI y = ( boxI ) ceil ( this->y / BOX_LENGTH );
	KynaField *field_old;
	KynaField *field;
	int pos = this->x % BOX_LENGTH;
	int halflength = BOX_LENGTH/2;

	if ( direct && lastx!=-1){
		item->setAnimations ( settings->lefttiles,200 );
		item->start ( -1 );
		lastx=-1;
		lasty=0;
	}

	field = level->getField ( x-1,y );

	if ( pos > halflength || field->unitKnocking ( this ) )
	{
		this->x -= settings->movespeed;

		if ( x != ( boxI ) ceil ( this->x / BOX_LENGTH ) || y != ( boxI ) ceil ( this->y / BOX_LENGTH ) )
		{
			field_old = level->getField ( x,y );
			field_old->unitLeave ( this );
			field->unitEnter ( this );
		}

		if ( this->y % BOX_LENGTH < halflength )
		{
			if ( movey>=0 )
			{
				if ( direct ) movey=0;
				if ( direct ) moveDown ( false );
			}
		}
		else if ( this->y % BOX_LENGTH > halflength )
		{
			if ( movey<=0 )
			{
				if ( direct ) movey=0;
				if ( direct ) moveUp ( false );
			}
		}

		return true;
	}
	else
	{
		if ( this->y % BOX_LENGTH < halflength )
		{
			field = level->getField ( x-1,y-1 );
			if ( field->unitKnocking ( this ) )
			{
				if ( movey<=0 )
				{
					if ( direct ) movey=0;
					if ( direct ) moveUp ( false );
				}
			}
		}
		else if ( this->y % BOX_LENGTH > halflength )
		{
			field = level->getField ( x-1,y+1 );
			if ( field->unitKnocking ( this ) )
			{
				if ( movey>=0 )
				{
					if ( direct ) movey=0;
					if ( direct ) moveDown ( false );
				}
			}
		}
		return false;
	}
}

bool KynaUnit::moveUp ( bool direct )
{
	boxI x = ( boxI ) ceil ( this->x / BOX_LENGTH );
	boxI y = ( boxI ) ceil ( this->y / BOX_LENGTH );
	KynaField *field_old;
	KynaField *field;
	int pos = this->y % BOX_LENGTH;
	int halflength = BOX_LENGTH/2;

	if ( direct && lasty!=-1){
		item->setAnimations ( settings->toptiles,200 );
		item->start ( -1 );
		lasty=-1;
		lastx=0;
	}

	field = level->getField ( x,y-1 );



	if ( pos > halflength || field->unitKnocking ( this ) )
	{

		this->y -= settings->movespeed;

		if ( x != ( boxI ) ceil ( this->x / BOX_LENGTH ) || y != ( boxI ) ceil ( this->y / BOX_LENGTH ) )
		{
			field_old = level->getField ( x,y );
			field_old->unitLeave ( this );
			field->unitEnter ( this );
		}

		if ( this->x % BOX_LENGTH < halflength )
		{
			if ( movex>=0 )
			{
				if ( direct ) movex=0;
				if ( direct ) moveRight ( false );
			}
		}
		else if ( this->x % BOX_LENGTH > halflength )
		{
			if ( movex<=0 )
			{
				if ( direct ) movex=0;
				if ( direct ) moveLeft ( false );
			}
		}

		return true;
	}
	else
	{

		if ( this->x % BOX_LENGTH < halflength )
		{
			field = level->getField ( x-1,y-1 );
			if ( field->unitKnocking ( this ) )
			{
				if ( movex<=0 )
				{
					if ( direct ) movex=0;
					if ( direct ) moveLeft ( false );
				}
			}
		}
		else if ( this->x % BOX_LENGTH > halflength )
		{
			field = level->getField ( x+1,y-1 );
			if ( field->unitKnocking ( this ) )
			{
				if ( movex>=0 )
				{
					if ( direct )	movex=0;
					if ( direct ) moveRight ( false );
				}
			}
		}

		return false;
	}
}

bool KynaUnit::moveDown ( bool direct )
{
	boxI x = ( boxI ) ceil ( this->x / BOX_LENGTH );
	boxI y = ( boxI ) ceil ( this->y / BOX_LENGTH );
	KynaField *field_old;
	KynaField *field;
	int pos = this->y % BOX_LENGTH;
	int halflength = BOX_LENGTH/2;

	if ( direct && lasty!=1){
		item->setAnimations ( settings->downtiles,200 );
		item->start ( -1 );
		lasty=1;
		lastx=0;
	}

	field = level->getField ( x,y+1 );

	if ( pos < halflength || field->unitKnocking ( this ) )
	{
		this->y += settings->movespeed;

		if ( x != ( boxI ) ceil ( this->x / BOX_LENGTH ) || y != ( boxI ) ceil ( this->y / BOX_LENGTH ) )
		{
			field_old = level->getField ( x,y );
			field_old->unitLeave ( this );
			field->unitEnter ( this );
		}

		if ( this->x % BOX_LENGTH < halflength )
		{
			if ( movex>=0 )
			{
				if ( direct ) movex=0;
				if ( direct ) moveRight ( false );
			}
		}
		else if ( this->x % BOX_LENGTH > halflength )
		{
			if ( movex<=0 )
			{
				if ( direct ) movex=0;
				if ( direct ) moveLeft ( false );
			}
		}
		return true;
	}
	else
	{

		if ( this->x % BOX_LENGTH < halflength )
		{
			field = level->getField ( x-1,y+1 );
			if ( field->unitKnocking ( this ) )
			{
				if ( movex<=0 )
				{
					if ( direct ) movex=0;
					if ( direct ) moveLeft ( false );
				}
			}
		}
		else if ( this->x % BOX_LENGTH > halflength )
		{
			field = level->getField ( x+1,y+1 );
			if ( field->unitKnocking ( this ) )
			{
				if ( movex>=0 )
				{
					if ( direct ) movex=0;
					if ( direct ) moveRight ( false );
				}
			}
		}
		return false;
	}
}

boxI KynaUnit::getBoxX()
{
	return ( boxI ) ceil ( x/BOX_LENGTH );
}

boxI KynaUnit::getBoxY()
{
	return ( boxI ) ceil ( y/BOX_LENGTH );
}



void KynaUnit::setPosition ( boxI x,boxI y )
{
	this->x = x*BOX_LENGTH+BOX_LENGTH/2;
	this->y = y*BOX_LENGTH+BOX_LENGTH/2;
}

bool KynaUnit::fireBomb()
{
	return true;
}

bool KynaUnit::move ( dirI x, dirI y )
{
	bool result;

	if ( y==0 )
	{
		if ( x < 0 )
			result = moveLeft ( true );

		else if ( x > 0 )
			result = moveRight ( true );
	}
	else if ( x == 0 )
	{
		if ( y < 0 )
			result = moveUp ( true );

		else if ( y > 0 )
			result = moveDown ( true );
	}
	else
	{
		if ( x < 0 )
			result = moveLeft ( false );
		else if ( x > 0 )
			result = moveRight ( false );
		else	if ( y < 0 )
			result = moveUp ( false );

		else if ( y > 0 )
			result = moveDown ( false );
	}

	if(x==0 && y==0)
		item->stop();


	item->setOffset ( this->x - UNIT_LENGTH / 2*PX_MULTI, this->y - UNIT_LENGTH / 2*PX_MULTI );

	if(view!=NULL)
			view->centerOn ( item );

	return result;

}

int KynaUnit::getType()
{
	return settings->type;
}

int KynaUnit::getMoveSpeed()
{
	return settings->movespeed;
}

void KynaUnit::setControl ( KynaControl * control )
{
	this->control = control;

	connect ( control, SIGNAL ( move ( dirI,dirI ) ),this, SLOT ( move ( dirI,dirI ) ) );
	connect ( control, SIGNAL ( placeBomb() ),this, SLOT ( placeBomb() ) );
	connect ( control, SIGNAL ( fireBomb() ),this, SLOT ( fireBomb() ) );
}

/**
 * @brief returns if the unit is dead or not
 * @return 
 */
bool KynaUnit::isDead()
{
	if(mode == MODE_UNIT_DEAD)
		return true;
	else
		return false;
}

void KynaUnit::dieNow()
{
	if(mode != MODE_UNIT_DEAD ){ 	//Nobody needs to die twice

		//set the deadMovie
		item->setAnimations(settings->deadtiles,0);
		item->start(0);
	
		qDebug() << settings->name << "died";
	
		//Set the mode
		mode = MODE_UNIT_DEAD;

		//public the death to control (or level TODO)
		emit die();
		level->checkForLevelEnd();
	}
}

KynaUnit::~ KynaUnit()
{
	if(control!=NULL){
		disconnect(control,0,0,0);
		delete control;
	}
	qDebug() << "Delete Unit";

}

