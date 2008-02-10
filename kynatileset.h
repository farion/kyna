#ifndef KYNATILESET_H
#define KYNATILESET_H

#include <QMap>
#include <QString>
#include <QPixmap>
#include <QDebug>

#include "defines.h"

class KynaTileset
{
	private:
		bool loadPixmap( QString filename);


	public:
		QMap<QString, QPixmap*> pixmaps;
		KynaTileset();
		QPixmap* getTile( QString filename );
		

};

#endif
