#include <cmath>
#include <iostream>

#include <QtXml>
#include <QPaintEvent>
#include <QPainter>
#include <QWidget>
#include <QDebug>
#include <QTime>

#include "kynalevel.h"
#include "kynawindow.h"


/* Start of KynaLevel */

KynaLevel::KynaLevel ( KynaWindow *window,LevelSettings settings )
{
	scene = new QGraphicsScene();
	this->window = window;
	goodies = new QList<KynaGoodie*>;

	this->settings = settings;

	tileset =  KynaTileset();
	//Initialize the random-generator
	QTime midnight ( 0, 0, 0 );
	qsrand ( midnight.secsTo ( QTime::currentTime() ) );


	generate();
}


void KynaLevel::start()
{
	//TODO

}


void KynaLevel::generate ( )
{

	qDebug() << "addUnits";
	addUnits();

	qDebug() << "init Fields";
	initializeFields();

	qDebug() << "fillFields";
	fillFreeFields ();

	qDebug() << "place Fields";
	placeFields();

	qDebug() << "place Units";
	placeUnits();

	qDebug() << "start KIs";
	startKIs();
}

void 	KynaLevel::startKIs()
{

	for ( int i = 0; i < units.size(); i++ )
	{
		if ( units[i]->getType() ==  UNIT_TYPE_PLAYER )
		{
			QList<int> keys;
			keys << Qt::Key_Left << Qt::Key_Right << Qt::Key_Up << Qt::Key_Down << Qt::Key_Space;
			KynaPlayer *control =  new KynaPlayer ( units[i],this,keys );
			units[i]->setControl(control);
			keycontrols.append ( control );
		}
		else
		{
  			KynaKI *kynaki = new KynaKI ( units[i],this );
			units[i]->setControl(kynaki);
   		kynaki->startThinking();

		}
	}
}

void  KynaLevel::placeUnits ( )
{
	KynaField * field;
	for ( int i = 0; i < units.size(); i++ )
	{
		field = getField ( units[i]->getBoxX(),units[i]->getBoxY() );
		field->unitEnter ( units[i] );
	}
}

KynaField* KynaLevel::getField ( boxI x,boxI y )
{

	return fields[y*this->getWidth() +x];

}

void KynaLevel::keyPressEvent ( QKeyEvent *event )
{

	switch ( event->key() )
	{
		default:
			for ( int i=0; i < keycontrols.size();i++ )
			{
				keycontrols.at ( i )->keyPressEvent ( event );
			}
	}
}

void KynaLevel::keyReleaseEvent ( QKeyEvent *event )
{
	switch ( event->key() )
	{
		default:
			for ( int i=0; i < keycontrols.size();i++ )
			{
				keycontrols.at ( i )->keyReleaseEvent ( event );
			}
	}
}


void KynaLevel::placeFields()
{
	boxI x,y;

	KynaField *currentField;

	for ( y=0;y<this->getHeight();y++ )   /* go through the fields */
	{
		for ( x=0;x<this->getWidth();x++ )
		{
			currentField = getField ( x,y );
			currentField->placeOnLevel();
		}
	}
}

//TODO used?
KynaUnit* KynaLevel::getPlayer ( int i )
{
	if ( i < units.size() && i >= 0 )
		return units[i];
	else
		return NULL;
}

void KynaLevel::addUnit ( KynaUnit *unit )
{
	units.append ( unit );
	units.last()->placeOnLevel();


}


void KynaLevel::initializeFields()
{

	boxI x,y;
	KynaField *curField;

	qDebug() <<settings.height<<" " <<settings.width;


	//generate a KynaAnimation for all the Fields
	QList<QList<QString> > aniData;
	QList<QString> animation;
	animation.append ( "tileset/default/gras.png" );
	aniData.append ( animation );
	QList<int> aniTime;
	aniTime.append ( 20 );


	for ( y=0;y<settings.height;y++ )   /* go through the fields */
	{
		for ( x=0;x<settings.width;x++ )
		{

			if ( x==0 && y==0 ) //linke obere Ecke
				curField = new KynaField ( x,y,this,FIELD_WALL_CORNER_LT,&tileset );

			else if ( x== 0 && y== this->getHeight()-1 ) //links untere Ecke
				curField = new KynaField ( x,y,this,FIELD_WALL_CORNER_LB, &tileset );

			else if ( x== this->getWidth()-1 && y== 0 ) //rechts obere Ecke
				curField = new KynaField ( x,y,this, FIELD_WALL_CORNER_RT, &tileset );

			else if ( x== this->getWidth()-1 && y== this->getHeight()-1 ) //rechts untere Ecke
				curField = new KynaField ( x,y,this,FIELD_WALL_CORNER_RB, &tileset );

			else if ( x==0 ) //linker Rand
				curField = new KynaField ( x,y,this, FIELD_WALL_BORDER_L, &tileset );

			else if ( y==0 ) //oberer Rand
				curField = new KynaField ( x,y,this, FIELD_WALL_BORDER_T, &tileset );

			else if ( x== this->getWidth()-1 ) //rechter Rand
				curField = new KynaField ( x,y,this,FIELD_WALL_BORDER_R , &tileset );

			else if ( y== this->getHeight()-1 ) //unterer Rand
				curField = new KynaField ( x,y,this,FIELD_WALL_BORDER_B, &tileset );


			else if ( y%2==0 && x%2==0 )		// feste Blï¿½cke
				curField = new KynaField ( x,y,this,FIELD_WALL_INDESTRUCTIBLE , &tileset );

			else
			{
				curField = new KynaField ( x,y,this,FIELD_FREE , &tileset );
				boxCoord bc;
				bc.x = x;
				bc.y = y;
				emptyFields.append ( bc );
			}

			fields.append ( curField );
		}
	}
}

void KynaLevel::fillFreeFields ( )
{
	int i,j,k,randi;
	boxCoord tmp;

	//mix empty fields
	for ( j=0;j < 5;j++ )
	{
		for ( i=0;i<emptyFields.size() ;i++ )
		{
			tmp = emptyFields[i];
			randi = qrand() % ( emptyFields.size()-1 );
			emptyFields[i] = emptyFields[randi];
			emptyFields[randi] = tmp;
		}
	}

	int fieldsToFill = ( int ) ( ceil ( ( double ) emptyFields.size() * ( ( double ) settings.fill/100 ) ) );
	int filledFields = 0;

 	bool fieldFillable;

	KynaField *currentField;
	KynaUnit *unit;

	//The mixed fields can be filled from the beginning
	for ( i=0;i < emptyFields.size();i++ )
	{
		currentField = getField ( emptyFields[i].x,emptyFields[i].y );

		fieldFillable=true;

		//check if there is a unit in the neighborhood
		for ( k=0; k < units.size(); k++ )
		{
			unit = units[k];

			//player needs room to place boombs
			if ( unit->getType() == UNIT_TYPE_PLAYER )
			{
				if (	(	(	unit->getBoxX() == emptyFields[i].x-1  //horizontal
				         || unit->getBoxX() == emptyFields[i].x+1	)
				        &&
				        (	unit->getBoxY() == emptyFields[i].y	)
				     )
				        ||
				        (	(	unit->getBoxY() == emptyFields[i].y-1 //vertical
				            || unit->getBoxY() == emptyFields[i].y+1 )
				          &&
				          (	unit->getBoxX() == emptyFields[i].x	)
				        )
				        ||
				        (	unit->getBoxX() == emptyFields[i].x //units is standing here
				          && unit->getBoxY() == emptyFields[i].y	)
				   )
					fieldFillable = false;
			}
			//other units only needs one Field
			else
			{
				if (	unit->getBoxX() == emptyFields[i].x
				        && unit->getBoxY() == emptyFields[i].y	)
					fieldFillable = false;
			}
		}

		//if there is no reason to let this field free, fill it
		if ( fieldFillable )
		{
			if ( fieldsToFill>filledFields )
			{
				currentField->setFieldType ( FIELD_WALL_DESTRUCTIBLE );

				//set the exit
				if ( filledFields==0 ) 
				{
					KynaExit *exit = new KynaExit (settings.exit, this,currentField, &tileset );
					currentField->setExit ( exit );
					this->exit = exit;
				}
				 // now fill in the goodies
				else	if ( settings.goodies->size() >= filledFields ) 
				{

					KynaGoodie *goodie = new KynaGoodie ( settings.goodies->at ( filledFields-1 ),this,currentField, &tileset );
					currentField->setGoodie ( goodie );
					goodies->append ( goodie );
				} 
				filledFields++;
			}
			else
			{
				break;
			}
		}

	}

	if ( fieldsToFill-filledFields > 0 )
		qDebug() << "Levelgenerator:		There are no more open fields to fill. It should be another " << (fieldsToFill-filledFields) << " fields filled.";
}

KynaWindow * KynaLevel::getWindow()
{
	return window;
}

void KynaLevel::addUnits()
{
	//TODO Woher kommt das control? => Spieleinstellungen: Level spielen wollen -> Level auslesen -> Spieler und Controls verteilen (Schnittstelle nötig) -> Level starten

	UnitSettings *unitsettings;

	for ( int i = 0; i < settings.units->size(); i++ )
	{
		unitsettings = settings.units->at ( i );
		KynaUnit *unit = new KynaUnit (
		    this,
		    &tileset,
		    unitsettings
		);


		addUnit ( unit );
		qDebug() << "Level added Player" << unitsettings->name;
	}
}

void KynaLevel::addItem ( QGraphicsPixmapItem * item )
{
	scene->addItem ( item );
}

void KynaLevel::removeItem(QGraphicsPixmapItem * item)
{
	scene->removeItem ( item );
}



boxI KynaLevel::getHeight()
{
	return ( boxI ) settings.height;
}

boxI KynaLevel::getWidth()
{
	return ( boxI ) settings.width;
}

KynaTileset * KynaLevel::getTileset()
{
	return &tileset;
}

void KynaLevel::checkForLevelEnd()
{
	int playerAlive=0;
	int enemyAlive=0;
	int playerDead=0;
	int enemyDead=0;

	for(int i = 0; i < units.size(); i++)
	{
		if(!units[i]->isDead())
			if(units[i]->getType() == UNIT_TYPE_PLAYER )
				playerAlive++;
			else if (units[i]->getType() == UNIT_TYPE_ENEMY )
				enemyAlive++;
		else
			if(units[i]->getType() == UNIT_TYPE_PLAYER )
				playerDead++;
			else if (units[i]->getType() == UNIT_TYPE_ENEMY )
				enemyDead++;
	}

	//If needed activate exit
	if(enemyAlive == 0 && !exit->isActive())
	{
		exit->setActive();
	}

	//Wins does not mean End, there is maybe an exit to find !! TODO

	if(playerAlive==0 && enemyAlive == 0){
		qDebug() << "All dead, nobody wins";
		animateEnd();
	}

	if(playerAlive==0){
		qDebug() << "All player dead.";
		animateEnd();
	}

	if(playerAlive==1 && enemyAlive==0)
		qDebug() << "Player wins";

	if(playerAlive==1 && playerDead != 0) //Multiplayer TODO
		qDebug() << "Player wins Multiplayer";


}

 void KynaLevel::exitIn()
 {	
 	window->level = NULL;
	animateEnd();
  	delete this;
 }

KynaLevel::~ KynaLevel()
{
	exit = NULL;

	for(int i = 0; i < fields.size(); i ++)
	{
		delete fields[i];
	}
	for(int i = 0;i < units.size(); i++)
	{
		delete units[i];
	}

	for(int i = 0;i < goodies->size(); i++)
	{
		delete goodies->at(i);
	}




	qDebug() << "deletion of level complete";
}

QGraphicsScene * KynaLevel::getScene()
{
	return scene;
}

void KynaLevel::animateEnd()
{
	endTimer = new KynaTimer();
	connect(endTimer,SIGNAL(timeout()),this,SLOT(animateEndFrame()));
	connect(endTimer,SIGNAL(end()),this,SLOT(emitEnd()));
	QPixmap pixmap = QPixmap(scene->width(),scene->height());
	pixmap.fill(QColor(0,0,0,0));
	overlay = new QGraphicsPixmapItem(pixmap);
	overlay->setOffset(0,0);
	addItem(overlay);
	overlay->setZValue(ZINDEX_OVERLAY);
	endTimer->startTimes(20,20);
}

void KynaLevel::animateEndFrame()
{
	int alpha = 255*endTimer->getProgress();
	QPixmap pixmap = QPixmap(scene->width()-2,scene->height()-2);
	pixmap.fill(QColor(255,255,255,alpha));
 	overlay->setPixmap(pixmap);
	overlay->setOffset(0,0);

	
}

void KynaLevel::emitEnd()
{
	emit end();
}
