#ifndef KYNAWINDOW_H
#define KYNAWINDOW_H

#include <QtGui>

#include "kynaunit.h"
#include "kynalevel.h"
#include "kynatimer.h"
#include "kynasettingsreader.h"

class KynaWindow  : public QMainWindow
{

		Q_OBJECT

	public:
		KynaWindow();
		void keyPressEvent ( QKeyEvent *event );
		void keyReleaseEvent ( QKeyEvent *event );
		KynaLevel *level;


	private:
		QGridLayout *mainLayout;
		QVBoxLayout *buttonLayout;
		QGridLayout *viewLayout;
		QList<QGraphicsView*> views;

		void cleanLayout(QLayout *layout);

		void makeLevel();
		void setViews();
		QGridLayout* setViewLayout ( int viewCount );
		void runLevel(int i);

		QMenu *mnuGame;
		QMenu *mnuSettings;
		QMenu *mnuHelp;
		QAction *actStartSingleMap;
		QAction *actStartCampaign;
		QAction *actMultiplayer;
		QAction *actLoadGame;
		QAction *actSaveGame;
		QAction *actQuitGame;
		QAction *actSettings;
		QAction *actHelp;
		QAction *actAbout;

		void createActions();
		void createMenu();

		void showStartScreen();

	public slots:
		void stopLevel(); //TODO weg damit
		void showMainMenu();

		void startSingleMap();
		void startCampaign();
		void startMultiplayer ();
		void  loadGame();
		void saveGame ();
		void quitGame ();
		void showSettings ();
		void showHelp ();
		void showAbout ();

	private slots:
		void levelend();


};

#endif
