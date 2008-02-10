#ifndef DYNALEVEL_H
#define DYNALEVEL_H

//Qt
#include <QMultiMap>
#include <QtGui>
#include <QPainter>
#include <QColor>
#include <QGraphicsScene>
#include <QList>

//Kyna
#include	"defines.h"
#include "kynatimer.h"
#include "kynatypes.h"
#include "kynafield.h"
#include "kynaplayer.h"
#include "kynaki.h"
#include "kynagoodie.h"
#include	"kynaexit.h"

class KynaPlayer;

class KynaWindow;

class KynaField;

class KynaLevel : public QWidget
{

	Q_OBJECT;

public:
	/**
	 * Initialization of a Level, by reading the matching file and setting up the needed values.
	 * @param window
	 * @param scene
	 * @param levelfilename
	 */
	KynaLevel ( KynaWindow *window,LevelSettings  settings);
	~KynaLevel();
	QGraphicsScene* getScene();
	KynaWindow* getWindow();
	void start();
	KynaField* getField ( boxI x,boxI y );
	KynaUnit* getPlayer ( int i ); //TODO
	QList<KynaUnit*> getPlayerToView(); //TODO
	void  placeUnits ( );
	void addItem( QGraphicsPixmapItem *item);
	void removeItem( QGraphicsPixmapItem *item);
	boxI getHeight();
	boxI getWidth();
	KynaTileset* getTileset();
	QGraphicsScene *scene;
	QList<KynaPlayer*> keycontrols;
 	void exitIn();
	

public slots:
	void keyPressEvent ( QKeyEvent *event );
	void keyReleaseEvent ( QKeyEvent *event );
	void checkForLevelEnd();
	void animateEndFrame();
	void emitEnd();

private:
	QList<KynaField*> fields;
	QList<boxCoord> emptyFields;
	void initializeFields();
	void fillFreeFields ( );
	QList<KynaUnit*> units;
	LevelSettings settings;
	void placeFields();

	KynaWindow *window;
	KynaTileset tileset;
	void generate ( );
 	void addUnit ( KynaUnit *unit ); //TODO
	void addUnits ();
	void startKIs (); //TODO
	void animateEnd();


	KynaExit *exit;
	QList<KynaGoodie*> *goodies;

	KynaTimer *endTimer;
	QGraphicsPixmapItem *overlay;
	

signals:
	
	void end();
};
#endif
