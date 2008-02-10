#include "kynaitem.h"
#include <iostream>

KynaItem::KynaItem()
{
	this->tileset = NULL;
	item = new KynaPixmapItem(tileset);
}

void KynaItem::setTileset ( KynaTileset *tileset )
{
	this->tileset = tileset;
}


boxI KynaItem::getBoxX()
{
	return x;
}

boxI KynaItem::getBoxY()
{
	return y;
}

