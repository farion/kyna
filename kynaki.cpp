#include <cmath>
#include <QTime>
#include <iostream>

#include "kynalevel.h"
#include "kynaki.h"

KynaKI::KynaKI ( KynaUnit *unit, KynaLevel *level ) : KynaControl( )
{

	this->level = level;

	movex = 0;
	movey = 0;
	myDir = qrand() % 4;
	this->unit = unit;


	
	thinking = false;
	dirChanged = true;

	thinkTimer = new QTimer();
	connect ( thinkTimer, SIGNAL ( timeout() ), this, SLOT ( think() ) );
	connect ( unit, SIGNAL ( die() ), this, SLOT ( die() ) );

	QTime midnight ( 0, 0, 0 );
	qsrand ( midnight.secsTo ( QTime::currentTime() ) );
}

void KynaKI::startThinking()
{
	if ( thinking == false ) {
		thinking = true;
		think();
		thinkTimer->start ( 40 );
	}
}

void KynaKI::die()
{
	stopThinking();
}

void KynaKI::stopThinking()
{
	if ( thinking == true )
		thinking = false;
}

//TODO Grafik muss hier raus und nach Unit
void KynaKI::think()
{

	if ( thinking == true ) {

		int oldMyDir = myDir;

		if(unit->getMoveSpeed()<=0)
			return;

		if ( qrand() % ( 800 / unit->getMoveSpeed() ) < 5 ) {
			int newMyDir = qrand() % 4;

			if ( newMyDir + myDir != 3 ) { /* verhindert stÃ¤ndiges umdrehen auf der geraden */
				myDir = newMyDir;
				dirChanged = true;
			}
		}


		switch ( myDir ) {
			case NORTH:

				if ( unit->move(0,-1) == false ) {
					myDir = qrand() % 4;
					dirChanged = true;
				}

				break;

			case EAST:

				if ( unit->move(1,0) == false ) {
					myDir = qrand() % 4;
					dirChanged = true;
				}

				break;

			case SOUTH:

				if ( unit->move(0,1) == false ) {
					myDir = qrand() % 4;
					dirChanged = true;
				}

				break;

			case WEST:

				if ( unit->move(-1,0) == false ) {
					myDir = qrand() % 4;
					dirChanged = true;
				}

				break;

			default:
				std::cout << "Sorry" << std::endl;
		}


		if ( lastDir == myDir && dirChanged == true ) {
			dirChanged = false;

		
		}

		lastDir = oldMyDir;
	}

}

KynaKI::~ KynaKI()
{
	qDebug() << "Delete KynaKI";
	thinkTimer->stop();
}

