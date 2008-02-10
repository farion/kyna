#ifndef KYNAPIXMAPITEM_H
#define KYNAPIXMAPITEM_H

//Qt
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

#include "kynatileset.h"


class KynaPixmapItem : public QObject, public QGraphicsPixmapItem
{

	Q_OBJECT

public:
	KynaPixmapItem(KynaTileset *tileset);
	~KynaPixmapItem();
	void setAnimations(QList<QString> *filenames, int interval);
	void setAnimations(QList<QString> *filenames, QList<int> *interval);
	bool start(int rounds=0);
	void pause();
	void unpause();
	void stop();
	void talk();

private slots:
	void nextFrame();	

private:
	KynaTileset *tileset;
	QTimer *animationTimer;
	QList<QPixmap> *pixmaps;
	QList<int> *interval;
	int frame;
	int rounds;


};

#endif
