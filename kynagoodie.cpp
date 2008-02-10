#include "kynagoodie.h"
#include "kynafield.h"

KynaGoodie::KynaGoodie ( GoodieSettings *settings, KynaLevel *level,KynaField *field,KynaTileset *tileset )
		: KynaItem()
{
	x = field->getBoxX();
	y = field->getBoxY();
	this->tileset = tileset;

	qDebug() << "Goodie on " << x << ":" << y;

	this->field = field;
	this->level = level;
	this->settings = settings;

	item = new KynaPixmapItem ( tileset );
}

/**
 * @brief Called if a unit enters the field, where the goodie is.
 * @param unit
 */
void KynaGoodie::meet ( KynaUnit * unit )
{
	if ( unit->getType() == UNIT_TYPE_PLAYER )
		grab ( unit );

}

void KynaGoodie::grab ( KynaUnit * unit )
{
	QMapIterator<int, int> i ( settings->buffs );
	while ( i.hasNext() )
	{
		i.next();
		unit->addBuff ( i.key(),i.value() );
	}

	destroy();
}

void KynaGoodie::destroy()
{
	field->setGoodie ( NULL );
	level->removeItem(item);
	delete item;

}



void KynaGoodie::placeOnLevel()
{

	qDebug() << "Goodie found";
	/*	if(buffs->size()<1)
			return;*/


	level->addItem ( item ) ;
	QList<int> *interval = new QList<int>;
	interval->append ( 400 );
	interval->append ( 350 );
	item->setAnimations ( &settings->tiles,interval );
	item->start ( -1 );
	item->setZValue ( ZINDEX_GOODIE );
	item->setOffset ( ( x - SHADOW_WIDTH ) * BOX_LENGTH* PX_MULTI , ( y - SHADOW_WIDTH ) *BOX_LENGTH * PX_MULTI );

}

void KynaGoodie::fire ( KynaBomb * bomb )
{
	qDebug() << "Goodie destroyed";
	this->destroy();
}

KynaGoodie::~ KynaGoodie()
{
	qDebug() << "Delete Goodie";
}

