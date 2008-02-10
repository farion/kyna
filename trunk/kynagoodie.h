#ifndef KYNAGOODIE_H
#define KYNAGOODIE_H

#include "kynaitem.h"
#include "kynaunit.h"

class KynaField;

class KynaGoodie : public KynaItem
{
public:
	KynaGoodie(GoodieSettings *settings,KynaLevel *level,KynaField *field,KynaTileset *tileset);
	~KynaGoodie();
	void addBuff(int type, int value); //TODO
	void meet(KynaUnit *unit);
	void fire(KynaBomb *bomb);
	void placeOnLevel(); //TODO
	void grab(KynaUnit *unit);
protected:
	KynaField *field;
	KynaLevel *level;
	void destroy(); //TODO
	GoodieSettings *settings;

};

#endif
