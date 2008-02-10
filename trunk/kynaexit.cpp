#include "kynaexit.h"
#include "kynafield.h"

KynaExit::KynaExit ( ExitSettings *settings, KynaLevel *level,KynaField *field,KynaTileset *tileset )
		: KynaItem()
{
	x = field->getBoxX();
	y = field->getBoxY();
	this->tileset = tileset;

	qDebug() << "Exit on " << x << ":" << y;

	mode = MODE_EXIT_INACTIVE;

	this->field = field;
	this->level = level;
	this->settings = settings;

	item = new KynaPixmapItem ( tileset );
}

/**
 * @brief Called if a unit enters the field, where the exit is.
 * @param unit
 */
/**
 * 
 * @param unit 
 */
void KynaExit::meet ( KynaUnit * unit )
{

	if( mode == MODE_EXIT_ACTIVE ){
		qDebug() << "Player enters Exit";
		level->exitIn();
	}

}



void KynaExit::placeOnLevel()
{

	qDebug() << "Exit found";

	level->addItem ( item ) ;
	QList<int> *interval = new QList<int>;
	if(mode == MODE_EXIT_INACTIVE)
	item->setAnimations ( &settings->inactivetiles,250);
	else
	item->setAnimations ( &settings->activetiles,250);
	item->start ( -1 );
	item->setZValue ( ZINDEX_GOODIE );
	item->setOffset ( ( x - SHADOW_WIDTH ) * BOX_LENGTH* PX_MULTI , ( y - SHADOW_WIDTH ) *BOX_LENGTH * PX_MULTI );

}

void KynaExit::fire ( KynaBomb * bomb )
{
	qDebug() << "Exit fired BAOOOOM";
}

void KynaExit::setActive()
{
	qDebug() << "exit is hot";
	mode = MODE_EXIT_ACTIVE;
	item->setAnimations ( &settings->activetiles,250 );
	item->start ( -1 );
}

bool KynaExit::isActive()
{
	if(mode == MODE_EXIT_ACTIVE)
		return true;
	else
		return false;
}

KynaExit::~ KynaExit()
{
	delete item;
}
