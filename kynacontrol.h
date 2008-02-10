#ifndef KYNACONTROL_H
#define KYNACONTROL_H

#include	<QObject>

#include "kynatypes.h"

class KynaLevel;

class KynaUnit;

class KynaControl : public QObject
{

Q_OBJECT

public:
    KynaControl();
	 void setUnit( KynaUnit *unit);

protected:
	KynaUnit *unit ;
	KynaLevel *level;
	dirI movex;
	dirI movey;

signals:
	void moveRight(bool);
	void moveLeft(bool);
	void moveUp(bool);
	void moveDown(bool);
	void placeBomb();
	void fireBomb();

};

#endif
