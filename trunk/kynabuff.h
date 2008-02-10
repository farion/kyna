#ifndef KYNABUFF_H
#define KYNABUFF_H

#include <QWidget>

class KynaUnit;

class KynaBuff : public QWidget
{

		Q_OBJECT

	protected:
		int buffType;
		KynaUnit *unit;
		int value;

	public:
		KynaBuff ( int buffType, int value, KynaUnit *unit );
		int getType();
		int getValue();
		void setValue ( int value );

};

#endif
