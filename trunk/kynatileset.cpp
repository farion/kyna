#include "kynatileset.h"


KynaTileset::KynaTileset()
{
}

bool KynaTileset::loadPixmap( QString filename)
{

	QPixmap *pixmap = new QPixmap();
	QString path;

	path.append(TILES_PATH);
	path.append("/");
 	path.append(filename);

	if ( !pixmap->load ( path ) )
	{
		qWarning() << "Cant load " << path;
		return false;
	}
 	pixmaps.insert(filename,pixmap);
	return true;

}

QPixmap * KynaTileset::getTile ( QString filename )
{
	if ( pixmaps.contains ( filename ) == false)
	{
		if( !loadPixmap( filename ) ){
			if(loadPixmap("missing.png"))
				return pixmaps[ "missing.png"];
			else
				return NULL;
			}
	}
	
	return pixmaps[ filename ];
}


