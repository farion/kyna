#ifndef KYNAEXIT_H
#define KYNAEXIT_H

#include "kynaitem.h"
#include "kynaunit.h"

class KynaField;

class KynaExit : public KynaItem
{
public:
	KynaExit(ExitSettings *settings,KynaLevel *level,KynaField *field,KynaTileset *tileset);
	~KynaExit();
	void meet(KynaUnit *unit);
	void fire(KynaBomb *bomb);
	void placeOnLevel();
	void setActive();
	bool isActive();
protected:
	KynaField *field;
	KynaLevel *level;
	ExitSettings *settings;
	int mode;

};

#endif
