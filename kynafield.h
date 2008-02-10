#ifndef KYNAFIELD_H
#define KYNAFIELD_H

#include <QApplication>
#include <QPainter>
#include <QWidget>
#include <QColor>
#include <QGraphicsPixmapItem>

#include "defines.h"
#include "kynalevel.h"
#include "kynaexit.h"
#include "kynaitem.h"
#include "kynabomb.h"

class KynaUnit;

class KynaGoodie;

class KynaField : public KynaItem
{
		Q_OBJECT

	private:
		KynaField *fields;
		KynaLevel *level;
		KynaUnit *unit;

		QList<KynaBomb*> bombs; //auf dem Feld liegende Bomben
		QList<KynaUnit*> units; //auf dem Feld befindende Einheiten
		QList<KynaBomb*> fired; //auf dem Feld befindende Explosion

//TODO Goodies implementieren
// 		QList <KynaGoodies*> goodies; //auf dem Feld befindenden Goodies

		int fieldType; //Feldtyp

		KynaExit *exit;

		bool isDestructible();
		bool isIndestructible();
		int destroyCounter;

		KynaGoodie *goodie;

		QTimer *fieldTimer;

	public:
		KynaField(boxI x,boxI y,KynaLevel *level,int fieldType,KynaTileset *tileset);
		~KynaField();

		//Functions needed for init
		void setLevel ( KynaLevel *level );
		void setPosition ( boxI x,boxI y );
		void placeOnLevel();
		void setFieldType ( int status );

		int getFieldType();

		bool unitKnocking ( KynaUnit *unit ); //Ob eine Einheit auf das Feld darf
		bool spying(); //Ob auf dem Feld eine Bombe gelegt werden kann

		bool unitEnter ( KynaUnit *unit );
		void unitLeave ( KynaUnit *unit );

		bool placeBomb ( KynaBomb *bomb );
		void removeBomb ( KynaBomb *bomb );

		int fire ( KynaBomb *bomb ); //Explosion erreicht Feld
		void removeFired ( KynaBomb *bomb ); //Explosion ist fertig mit diesem Feld

		void setExit ( KynaExit *exit);
		KynaExit* getExit();
	
		void setGoodie ( KynaGoodie *goodie );
		KynaGoodie* getGoodie();

	private slots:
		void destroyWall();	

	signals:
		void unitComesIn ( KynaUnit *unit ); //Benachrichtigung für bereits auf dem Feld befindliche Einheiten beim Eintritt einer neuen
};

#endif
