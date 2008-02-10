#ifndef KYNAUNIT_H
#define KYNAUNIT_H

//C++
#include <cmath>

//Qt
#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QPainter>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

//Kyna

#include "kynaitem.h"
#include "kynabomb.h"
#include "kynabuff.h"
#include "kynacontrol.h"

class KynaLevel;

class KynaBoard;

class KynaUnit : public KynaItem
{

		Q_OBJECT

	protected:
		KynaLevel *level;
		KynaBoard *board;

		int movespeed; //TODO Wegmachen, wenn kynaki von control erbt

		dirI x;
		dirI y;
		dirI movex;
		dirI movey;
		dirI lastx;
		dirI lasty;

		QList<KynaBomb*> bombs;
		QList<KynaBuff*> buffs;

		QGraphicsView *view;	
	
		UnitSettings *settings;
	
		KynaControl *control;

		bool moveRight ( bool direct = true );
		bool moveLeft ( bool direct = true );
		bool moveUp ( bool direct = true );
		bool moveDown ( bool direct = true );

	public:
		KynaUnit();
		KynaUnit (KynaLevel *level,  KynaTileset *tileset, UnitSettings *settings );
		~KynaUnit();

		void initUnitType ( QString unitname, QString type, QList<KynaBuff*> );
		void placeOnLevel();

		void setControl(KynaControl *control);

		int getMoveSpeed();

		int getType();

		void setAsMainUnitFor ( QGraphicsView *view );

		boxI getBoxX();
		boxI getBoxY();
		void setPosition ( boxI x,boxI y );

		void setName ( QString name );
		QString getName();

		bool addBuff ( int buffType,int value );
		bool removeBuff ( int buffType );
		int getBuff ( int buffType );

		void bombIsDone ( KynaBomb *bomb );

		void fire();
		void dieNow();

		bool isDead();

		void setTileset ( QPixmap *tileset ); //TODO evtl kann man das nach Items verschieben mit geeignetem Konzept

	signals:
		void die();

	public slots:

		void meet ( KynaUnit *unit );


		bool move(dirI x, dirI y);

		bool placeBomb();
		bool fireBomb(); //TODO
};

#endif

