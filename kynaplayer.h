#ifndef KYNAPLAYER_H
#define KYNAPLAYER_H

#include "kynaunit.h"
#include "kynacontrol.h"

class KynaPlayer : public KynaControl
{
		Q_OBJECT

	protected:
		QTimer *moveTimer;
		QList<int> keys;

	public:
		KynaPlayer ( KynaUnit *unit, KynaLevel *level, QList<int> keys  );
		~KynaPlayer();
		void startmove ( dirI x,dirI y );

	public slots:
		void keyPressEvent ( QKeyEvent *event );
		void keyReleaseEvent ( QKeyEvent *event );

	private slots:
		void move();
		void die();

	signals:
		void move(dirI x, dirI y);


};

#endif
