#ifndef KYNABOMB_H
#define KYNABOMB_H

#include <QTimer>

#include "kynaitem.h"

class KynaUnit;

class KynaLevel;

class KynaField;

class KynaBomb : public KynaItem
{

		Q_OBJECT;

	public:
		KynaBomb ( boxI x,boxI y,KynaUnit *unit, KynaLevel *level,int ticks,KynaTileset *tileset );
		~KynaBomb(); //TODO TempPixmaps löschen um den Speicher wieder frei zu kriegen
		void start();
		void explode();

	protected:
		int firetime;
		QList <QGraphicsPixmapItem*> fireList;
		QList <KynaField*> fields;
		KynaUnit *unit;
		KynaLevel *level;
		int ticks;
		QTimer *explodeTimer;

		void destroy();
		void fireDirection ( boxI modX, boxI modX );

	private slots:
		void tick();
		void animateFire();

	private:
		int range;


};

#endif
