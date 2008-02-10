#ifndef KYNAITEM_H
#define KYNAITEM_H

#include <QWidget>
#include <QPixmap>
#include <QtDebug>
#include <QGraphicsPixmapItem>

#include "defines.h"
#include "kynapixmapitem.h"
#include "kynatypes.h"
#include "kynatileset.h"
#include "helper.h"

class KynaLevel;


class KynaItem : public QWidget
{
	protected:
		boxI x;
		boxI y;
		QString tile;
		int mode;
		KynaTileset *tileset;

	public:
		KynaItem();
		KynaPixmapItem *item;
		boxI getBoxX();
		boxI getBoxY();
		void setTileset ( KynaTileset *tileset );
};

#endif
