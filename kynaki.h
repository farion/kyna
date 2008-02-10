#ifndef KYNAKI_H
#define KYNAKI_H

#include <kynaunit.h>

class KynaLevel;
class KynaUnit;

class KynaKI : public KynaControl 
{
		Q_OBJECT

	public:
		KynaKI ( KynaUnit *unit, KynaLevel *level );
		~KynaKI();
		void startThinking();
		void stopThinking();

	private:
		KynaUnit *unit;
		QTimer *thinkTimer;
		bool thinking;
		bool dirChanged;
		int lastDir;

	public slots:
		void die();

	private slots:
		void think();

	protected:
		int movex;
		int movey;
		int myDir;



};

#endif
