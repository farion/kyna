#include <QGraphicsView>
#include <iostream>
#include <cmath>

#include "kynalevel.h"
#include "kynaplayer.h"
#include "kynabomb.h"

KynaPlayer::KynaPlayer ( KynaUnit *unit, KynaLevel *level, QList<int> keys ) : KynaControl( )
{
	this->level = level;
	this->keys = keys;

	this->unit = unit;

	unit->setControl ( this );

	this->movex = 0;
	this->movey = 0;
	moveTimer = new QTimer();
	connect ( moveTimer, SIGNAL ( timeout() ), this, SLOT ( move() ) );
	connect ( unit, SIGNAL ( die() ), this, SLOT ( die() ) );
}

//TODO die TILES müssen von unit gehandelt werden

void KynaPlayer::keyPressEvent ( QKeyEvent *event )
{
	bool timerStart = false;

	if ( movex==0 && movey==0 )
		timerStart = true;

	if ( !event->isAutoRepeat() && !unit->isDead() )
	{
		if ( event->key() == keys[KEY_UP] )
		{
			movey = -1;
			if ( timerStart )
				moveTimer->start ( 40 );
		}
		else if ( event->key() == keys[KEY_DOWN] )
		{
			movey = 1;
			if ( timerStart )
				moveTimer->start ( 40 );
		}
		else if ( event->key() == keys[KEY_LEFT] )
		{
			movex = -1;
			if ( timerStart )
				moveTimer->start ( 40 );
		}
		else if ( event->key() == keys[KEY_RIGHT] )
		{
			movex = 1;
			if ( timerStart )
				moveTimer->start ( 40 );
		}
		else if ( event->key() == keys[KEY_BOMB] )
			unit->placeBomb();
		else
			event->ignore();
	}
}

void KynaPlayer::keyReleaseEvent ( QKeyEvent *event )
{
	if ( !event->isAutoRepeat()  && !unit->isDead() )
	{
		if ( event->key() == keys[KEY_UP] )
			movey = 0;
		else if ( event->key() == keys[KEY_DOWN] )
			movey = 0;
		else if ( event->key() == keys[KEY_LEFT] )
			movex = 0;
		else if ( event->key() == keys[KEY_RIGHT] )
			movex = 0;
		else
			event->ignore();

		if ( movex==0 && movey==0 )
		{
			moveTimer->stop();
		}
	}
}


void KynaPlayer::startmove ( dirI x, dirI y )
{
	if ( x != 0 )
	{
		this->movex = x;
	}
	else
	{
		this->movey = y;
	}

	move();
}

void KynaPlayer::die()
{
	movex = 0;
	movey = 0;
	moveTimer->stop();

}

//TODO Grafik muss hier raus und nach Unit
void KynaPlayer::move()
{
	if ( this->movex != 0 || this->movey != 0 )
	{
		emit move ( movex,movey );
	}
}

KynaPlayer::~ KynaPlayer()
{
	qDebug() << "Delete KynaPlayer";
	moveTimer->stop();
}
