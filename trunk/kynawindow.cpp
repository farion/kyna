#include "kynawindow.h"

KynaWindow::KynaWindow()
{

	level = NULL;
	setWindowTitle ( tr ( "Kyna Masters" ) );
	setFixedSize ( 840,700 );

	QWidget *widget = new QWidget ( this );
// 	widget->setStyleSheet("color: yellow;background-color: black");
	setCentralWidget ( widget );

	mainLayout = new QGridLayout();

	widget->setLayout ( mainLayout );

	createActions();
	createMenu();

	statusBar();

	showStartScreen();
}

void KynaWindow::setViews()
{
	KynaUnit *player;

	for ( int i =0; i < views.size() ; i++ )
	{
		QGraphicsScene *scene = level->getScene();
		views[i]->setScene ( scene );
		player = level->getPlayer ( i );
		player->setAsMainUnitFor ( views[i] );
// 	 	QGLFormat *format = new QGLFormat(QGL::DoubleBuffer);
// 				views[i]->setViewport(new QGLWidget(*format));
// 		views[i]->setFixedSize(15*48,13*48);
		views[i]->setCacheMode ( QGraphicsView::CacheBackground );
		views[i]->setRenderHints ( !QPainter::Antialiasing | !QPainter::SmoothPixmapTransform | !QPainter::TextAntialiasing | !QPainter::HighQualityAntialiasing );
		views[i]->setOptimizationFlags ( QGraphicsView::DontAdjustForAntialiasing | QGraphicsView::DontClipPainter | QGraphicsView::DontSavePainterState );
		views[i]->setHorizontalScrollBarPolicy (	Qt::ScrollBarAlwaysOff );
		views[i]->setVerticalScrollBarPolicy (	Qt::ScrollBarAlwaysOff );
		views[i]->setFocusPolicy ( Qt::NoFocus );
	}
}

void KynaWindow::makeLevel()
{
	KynaSettingsReader *reader = new KynaSettingsReader();

	LevelSettings settings = reader->readLevel ( "stage1" );

	level = new KynaLevel ( this,settings );

	connect ( level,SIGNAL ( end() ),this,SLOT ( levelend() ) );
}

void KynaWindow::keyPressEvent ( QKeyEvent *event )
{
	if ( level )
		level->keyPressEvent ( event );
	event->ignore();
}

void KynaWindow::keyReleaseEvent ( QKeyEvent *event )
{
	if ( level )
		level->keyReleaseEvent ( event );
	event->ignore();
}

QGridLayout* KynaWindow::setViewLayout ( int viewCount )
{
// 	for (int i = 0; i < viewLayout->count(); ++i)
// 		viewLyayout->removeWidget(viewLayout->itemAt(i));


	/*
		Zeilen = normal gerundete Wurzel aus der Anzahl der views
		Spalten = aufgerundete Wurzel aus der Anzahl der views
	*/
	viewLayout = new QGridLayout;

	views.clear();


	int rows = ( int ) round ( sqrt ( viewCount ) );
	int cols = ( int ) ceil ( sqrt ( viewCount ) );

	int sizeRow;
	int sizeCol;

	if ( viewCount == 1 )
	{
		sizeRow = 13*48;
		sizeCol = 15*48;
	}
	else
	{
		sizeRow = ( int ) floor ( ( 13*48 ) / ( double ) rows );
		sizeCol = ( int ) floor ( ( 16*48 ) / ( double ) cols );
	}



	for ( int i = 0; i < rows; i++ )
	{
		for ( int j = 0; j < cols; j++ )
		{
			if ( viewCount > j*rows+i )
			{
				views.append ( new QGraphicsView ( this ) );
 				views.last()->setFixedSize ( QSize ( sizeCol,sizeRow ) );
				views.last()->setStyleSheet("QGraphicsView { border: none }");
				viewLayout->addWidget ( views.last(),i,j );
			}
			else
				break;
		}
	}

	qDebug() << "SPLITMODE Views: " << views.size() << " ViewSize: " << sizeRow << "px X " << sizeCol << "px Grid: " << cols << " X " << rows;

	return viewLayout;
}

void KynaWindow::runLevel ( int i )
{
		levelend();

	cleanLayout ( mainLayout );
	qDebug() << "make Level";
	makeLevel();
	qDebug() << "set ViewLayout";
// 	mainLayout->addWidget ( new QWidget(),0,0 );
	mainLayout->addLayout ( setViewLayout ( i ),0,1 );
// 	mainLayout->addWidget ( new QWidget(),0,2 );
	qDebug() << "set Views";
	setViews();

	qDebug() << "doing GUI";

// 	qDebug() << viewsLayout.count();
}

void KynaWindow::stopLevel()
{

	for ( int i = 0; i < views.size(); i++ )
	{
		delete views[i];
	}
	views.clear();

	QLayoutItem *child;
	while ( ( child = viewLayout->takeAt ( 0 ) ) != 0 )
	{
		delete child;
	}
}


void KynaWindow::levelend()
{


	delete level;
	level = NULL;
// 	stopLevel();
	qDebug() << "Level ended.";
}

void KynaWindow::showMainMenu()
{
	


}

void KynaWindow::cleanLayout ( QLayout *layout )
{
	QLayoutItem *child;
	while ( ( child = layout->takeAt ( 0 ) ) != 0 )
	{

		if ( child->layout() )
		{
			qDebug() << "layout " << child->layout();
			cleanLayout ( child->layout() );
			delete child->layout();
		}
		else
		{
			delete child->widget();
		}
	}

}

void KynaWindow::createActions()
{
	actStartSingleMap = new QAction ( tr ( "&New Singlemap ..." ), this );
	actStartSingleMap->setShortcut ( tr ( "Ctrl+N" ) );
	actStartSingleMap->setStatusTip ( tr ( "Create a new singleplayer game with one selectable map." ) );
	connect ( actStartSingleMap, SIGNAL ( triggered() ), this, SLOT (startSingleMap() ) );

	actStartCampaign = new QAction ( tr ( "New &Campaign ..." ), this );
	actStartCampaign->setShortcut ( tr ( "Ctrl+C" ) );
	actStartCampaign->setStatusTip ( tr ( "Create a new singleplayer campaign game." ) );
	connect ( actStartCampaign, SIGNAL ( triggered() ), this, SLOT (startCampaign() ) );

	actMultiplayer = new QAction ( tr ( "&Multiplayer ..." ), this );
	actMultiplayer->setShortcut ( tr ( "Ctrl+M" ) );
	actMultiplayer->setStatusTip ( tr ( "Create a new multiplayer game." ) );
	connect ( actMultiplayer, SIGNAL ( triggered() ), this, SLOT (startMultiplayer() ) );

	actLoadGame = new QAction ( tr ( "&Load saved game ..." ), this );
	actLoadGame->setShortcut ( tr ( "L" ) );
	actLoadGame->setStatusTip ( tr ( "Loads a previous saved game." ) );
	connect ( actLoadGame, SIGNAL ( triggered() ), this, SLOT (loadGame() ) );

	actSaveGame = new QAction ( tr ( "&Save game ..." ), this );
	actMultiplayer->setShortcut ( tr ( "S" ) );
	actMultiplayer->setStatusTip ( tr ( "Save the current game state to a file." ) );
	connect ( actMultiplayer, SIGNAL ( triggered() ), this, SLOT (saveGame() ) );

	actQuitGame = new QAction ( tr ( "&Quit" ), this );
	actQuitGame->setShortcut ( tr ( "Ctrl+Q" ) );
	actQuitGame->setStatusTip ( tr ( "Quits the game" ) );
	connect ( actQuitGame, SIGNAL ( triggered() ), this, SLOT (quitGame() ) );

	actSettings = new QAction ( tr ( "&Settings" ), this );
	actSettings->setShortcut ( tr ( "Ctrl+S" ) );
	actSettings->setStatusTip ( tr ( "Quits the game" ) );
	connect ( actSettings, SIGNAL ( triggered() ), this, SLOT (showSettings() ) );

	actHelp = new QAction ( tr ( "&Help" ), this );
	actHelp->setShortcut ( tr ( "Ctrl+H" ) );
	actHelp->setStatusTip ( tr ( "Displays the help." ) );
	connect ( actHelp, SIGNAL ( triggered() ), this, SLOT (showHelp() ) );

	actAbout = new QAction ( tr ( "&About" ), this );
	actAbout->setShortcut ( tr ( "Ctrl+A" ) );
	actAbout->setStatusTip ( tr ( "Displays Information, about this game and the people who made it." ) );
	connect ( actAbout, SIGNAL ( triggered() ), this, SLOT (showAbout() ) );
}

void KynaWindow::createMenu()
{
	mnuGame = menuBar()->addMenu ( tr ( "&Game" ) );
	mnuGame->addAction ( actStartSingleMap );
	mnuGame->addAction ( actStartCampaign );
	mnuGame->addSeparator();
	mnuGame->addAction ( actMultiplayer );
	mnuGame->addSeparator();
	mnuGame->addAction ( actLoadGame );
	mnuGame->addAction ( actSaveGame );
	mnuGame->addSeparator();
	mnuGame->addAction ( actQuitGame );

	mnuSettings = menuBar()->addMenu ( tr ( "&Settings" ) );
	mnuSettings->addAction ( actSettings );

	mnuHelp = menuBar()->addMenu ( tr ( "&Help" ) );
	mnuHelp->addAction ( actHelp );
	mnuHelp->addSeparator();
	mnuHelp->addAction ( actAbout );
}

void KynaWindow::startSingleMap()
{
 	cleanLayout(mainLayout);
	runLevel(1);
}

void KynaWindow::startCampaign()
{
}

void KynaWindow::startMultiplayer()
{
}

void KynaWindow::loadGame()
{
}

void KynaWindow::saveGame()
{
}

void KynaWindow::quitGame()
{
}

void KynaWindow::showSettings()
{
}

void KynaWindow::showHelp()
{
}

void KynaWindow::showAbout()
{
}

void KynaWindow::showStartScreen()
{
 	cleanLayout(mainLayout);

	QLabel *lblLogo = new QLabel;
	lblLogo->setPixmap(QPixmap("data/logo.png"));
	mainLayout->setAlignment(Qt::AlignCenter);
	mainLayout->addWidget(lblLogo,0,0);
}
