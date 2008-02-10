#include <QTime>
#include <QColor>
#include <QPixmap>
#include <QRect>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <iostream>

#include "kynafield.h"
#include "kynaunit.h"

/**
 *
 * @param x
 * @param y
 * @param level
 * @param fieldType
 */
KynaField::KynaField ( boxI x,boxI y,KynaLevel *level,int fieldType,KynaTileset *tileset )
{
	unit = NULL;
	this->level = level;

	setPosition ( x,y );

	bombs = QList<KynaBomb*>();
	
	goodie = NULL;
	exit = NULL;

	item = new KynaPixmapItem ( tileset );

	setFieldType ( fieldType );

	this->tileset = tileset;

	fieldTimer = NULL;

	destroyCounter = 0;

}

void KynaField::setLevel ( KynaLevel *level )
{
	this->level = level;
}

void KynaField::setPosition ( boxI x, boxI y )
{
	this->x = x;
	this->y = y;
}

void KynaField::placeOnLevel()
{

	level->addItem ( item ) ;
	item->setOffset ( ( x - SHADOW_WIDTH ) * BOX_LENGTH* PX_MULTI , ( y - SHADOW_WIDTH ) *BOX_LENGTH * PX_MULTI );

}



/**
 * @brief Load Graphics and Animation and set z-index
 * @todo get files from general interface -> xml
 * @param fieldType
 */
void KynaField::setFieldType ( int fieldType )
{
	QList<QString> files;

	this->fieldType = fieldType;

	switch ( fieldType )
	{
		case FIELD_WALL_CORNER_LT:
			item->setZValue ( ZINDEX_FIELD_BORDER + y*level->getHeight() + x );
			files.append ( "wand_lt.png" );
			break;
		case FIELD_WALL_CORNER_LB:
			item->setZValue ( ZINDEX_FIELD_BORDER + y*level->getHeight() + x );
			files.append ( "wand_lb.png" );
			break;
		case FIELD_WALL_CORNER_RT:
			item->setZValue ( ZINDEX_FIELD_BORDER + y*level->getHeight() + x );
			files.append ( "wand_rt.png" );
			break;
		case FIELD_WALL_CORNER_RB:
			item->setZValue ( ZINDEX_FIELD_BORDER + y*level->getHeight() + x );
			files.append ( "wand_rb.png" );
			break;

		case FIELD_WALL_BORDER_L:
			item->setZValue ( ZINDEX_FIELD_BORDER + y*level->getHeight() + x );
			files.append ( "wand_l.png" );
			break;
		case FIELD_WALL_BORDER_T:
			item->setZValue ( ZINDEX_FIELD_BORDER + y*level->getHeight() + x );
			files.append ( "wand_t.png" );
			break;
		case FIELD_WALL_BORDER_R:
			item->setZValue ( ZINDEX_FIELD_BORDER + y*level->getHeight() + x );
			files.append ( "wand_r.png" );
			break;
		case FIELD_WALL_BORDER_B:
			item->setZValue ( ZINDEX_FIELD_BORDER + y*level->getHeight() + x );
			files.append ( "wand_b.png" );
			break;

		case FIELD_WALL_DESTRUCTIBLE:
			item->setZValue ( ZINDEX_FIELD_WALL + y*level->getHeight() + x );
			files.append ( "mauer.png" );
			break;
		case FIELD_WALL_INDESTRUCTIBLE:
			item->setZValue ( ZINDEX_FIELD_WALL + y*level->getHeight() + x );
			files.append ( "saeule.png" );
			break;
		case FIELD_FREE:
			item->setZValue ( ZINDEX_FIELD_FREE + y*level->getHeight() + x );
			files.append ( "gras.png" );
			break;
		default:
			item->setZValue ( ZINDEX_FIELD_BORDER + y*level->getHeight() + x );
			files.append ( "wand_l.png" );
	}

	item->setAnimations ( &files,0 );
	item->start ( 0 );
}

int KynaField::getFieldType()
{
	return this->fieldType;
}

bool KynaField::unitKnocking ( KynaUnit *unit )
{
	if (	( bombs.isEmpty() || unit->getBuff ( BUFF_GO_THROUGH_BOMBS ) >= 0 ) 			//bomb
	        && !isIndestructible()																//indestructible
	        && ( !isDestructible() || unit->getBuff ( BUFF_GO_THROUGH_WALLS ) >= 0 ) )  	//destructible
	{
		/* unit can enter */
		return true;
	}
	else
	{
		/* unit can not enter */
		return false;
	}
}

/* Returns true, if it is possible to place a bomb */
bool KynaField::spying ( )
{

	if ( bombs.isEmpty() && !isIndestructible() && !isDestructible() )
		return true;
	else
		return false;

}

bool KynaField::unitEnter ( KynaUnit *unit )
{
	if ( unitKnocking ( unit ) )
	{
		emit unitComesIn ( unit );

		/* unit gets a meet, if someone other enter */
		connect ( this, SIGNAL ( unitComesIn ( KynaUnit* ) ), unit, SLOT ( meet ( KynaUnit* ) ) );

		/* some fire here? */ /* needs to be improved for a no friendly fire buff */

		if ( fired.size() > 0 )
		{
			unit->fire();
		}

		//unit get the goodie
		if( unit->getType() == UNIT_TYPE_PLAYER && getFieldType() == FIELD_FREE && goodie != NULL ) {
			goodie->grab(unit);

		}

		//unit takes exit
		if( unit->getType() == UNIT_TYPE_PLAYER && getFieldType() == FIELD_FREE && exit != NULL ) {
			exit->meet(unit);

		}

		/* unit meets all the others  - all other units gets the meet already from the SIGNAL */
		for ( int i = 0; i < units.size(); i++ )
			unit->meet ( units.at ( i ) );

		/* add unit to fields unit list */
		units.append ( unit );

		return true;
	}
	else
	{
		return false;
	}
}

void KynaField::unitLeave ( KynaUnit *unit )
{
	/* disconnect from the unitEnter to get no signals from this field */
	disconnect ( this, 0, unit, 0 );

	/* remove the unit from the fields unit list */

	for ( int i = 0; i < units.size(); i++ )
	{
		if ( units.at ( i ) == unit )
		{
			units.removeAt ( i );
			break;
		}
	}
}

bool KynaField::placeBomb ( KynaBomb *bomb )
{
	if ( spying() )
	{
		bombs.append ( bomb );
		bomb->start();
		return true;
	}
	else
	{
		return false;
	}
}

void KynaField::removeBomb ( KynaBomb *bomb )
{
	for ( int i = 0; i < bombs.size(); i++ )
	{
		if ( bomb == bombs[i] )
		{
			bombs.removeAt ( i );
			return;
		}
	}

}

/**
 * @brief is fired up when bomb explosion reached this field
 * @return returns if the fire goes on or stop at this position
 */
int KynaField::fire ( KynaBomb *bomb )
{

	if(destroyCounter!=0)
		return FIRE_WAY_STOP;

	/* fire bomb that already on this field */
	for ( int i = 0; i < bombs.size();i++ )
	{
		bombs[i]->explode();
	}

	/* fire units, that are on this field */
	for ( int i = 0; i < units.size();i++ )
	{
		units[i]->fire();
	}

	//fire goodie if needed
	if( getFieldType() == FIELD_FREE && goodie != NULL )
		goodie->fire(bomb);

	int returnV;

	QList<QString> *list;

	switch ( getFieldType() )
	{
		case FIELD_WALL_DESTRUCTIBLE:
			destroyCounter = BOMB_FIRE_TIME;
			fieldTimer = new QTimer();
			list = new QList<QString>;
			list->append ( "mauer_explode.png" );
			item->setAnimations ( list,0 );
			item->start ( 0 );
			connect ( fieldTimer,SIGNAL ( timeout() ),this,SLOT ( destroyWall() ) );
			fieldTimer->start ( 20 );

			returnV =  FIRE_WAY_STOP;

			break;
		case FIELD_FREE:
			returnV = FIRE_WAY_CONTINUE;

			break;

		default:
			returnV = FIRE_WAY_STOP;
		break;
	}

	if ( returnV == FIRE_WAY_CONTINUE )
		fired.append ( bomb );

	return returnV;
}

void KynaField::removeFired ( KynaBomb *bomb )
{
	for ( int i = 0; i < fired.size(); i++ )
	{
		if ( bomb == fired[i] )
		{
			fired.removeAt ( i );
			return;
		}
	}

}

/*********** Private Functions ***************/

bool KynaField::isDestructible()
{
	switch ( getFieldType() )
	{
		case FIELD_WALL_DESTRUCTIBLE:
			return true;
			break;
		default:
			return false;
	}
}

bool KynaField::isIndestructible()
{
	switch ( getFieldType() )
	{
	case FIELD_FREE: case FIELD_WALL_DESTRUCTIBLE:
			return false;
			break;
		default:
			return true;
	}
}

void KynaField::destroyWall()
{
	if ( destroyCounter > 0 )
	{
		destroyCounter--;
	}
	else
	{

	 	destroyCounter=0;
		fieldTimer->stop();
		disconnect(fieldTimer,0,0,0);
		setFieldType ( FIELD_FREE );
		tile =  "free"; //TODO needed?
		qDebug() << "destroy " << x << ":" << y << " - " << destroyCounter;

		if( goodie != NULL)
			goodie->placeOnLevel();

		if( exit != NULL)
			exit->placeOnLevel();
 	}
}

void KynaField::setExit(KynaExit *exit)
{
	this->exit = exit;
}

KynaExit* KynaField::getExit()
{
	return exit;
}

void KynaField::setGoodie(KynaGoodie * goodie)
{
	this->goodie = goodie;
}

KynaGoodie * KynaField::getGoodie()
{
	return goodie;
}

KynaField::~ KynaField()
{
	for(int i = 0; i < bombs.size();i++)
		delete bombs[i];

	if(fieldTimer)
		fieldTimer->stop();
}


