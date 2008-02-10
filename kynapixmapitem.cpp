


#include "kynapixmapitem.h"

KynaPixmapItem::KynaPixmapItem(KynaTileset *tileset)
{
	animationTimer = new QTimer();
	this->tileset = tileset;
 	connect(animationTimer,SIGNAL(timeout()),this,SLOT(nextFrame()));
	pixmaps = new QList<QPixmap>;
	frame = 0;
	rounds = 0;
}

void KynaPixmapItem::setAnimations(QList<QString> *filenames, int interval)
{

	QList<int> *intervalList =  new QList<int>;
	for(int i = 0; i< filenames->size();i++)
		intervalList->append(interval);

	setAnimations(filenames,intervalList);
}


void KynaPixmapItem::setAnimations(QList<QString> *filenames, QList<int> *interval)
{
	if(filenames->size()>1)
		qDebug() << filenames->size();

	stop();
	pixmaps->clear();
	for(int i = 0; i < filenames->size(); i++ )
	{
		QPixmap pixmap = *tileset->getTile(filenames->at(i));
		if(!pixmap)
			qDebug()<< "PixmapERR";
		pixmaps->append(pixmap);
	}
	this->interval = interval;
}

bool KynaPixmapItem::start(int rounds)
{
	stop();

	if(pixmaps->size() == 0){
		qDebug()<< "No Pixmaps there to show";
		return false;
	}
	setPixmap(pixmaps->at(0));

	if(pixmaps->size() >1 ){
		animationTimer->start(interval->at(0));
		this->rounds = rounds;
	}

	return true;
}


void KynaPixmapItem::stop()
{
	if(animationTimer->isActive())
		animationTimer->stop();
	frame = 0;

}

void KynaPixmapItem::pause()
{
	if(animationTimer->isActive())
		animationTimer->stop();
}

void KynaPixmapItem::unpause()
{
	animationTimer->start(interval->at(frame));
}

void KynaPixmapItem::nextFrame()
{
	if(rounds == 0)
		return;

	if(frame >= pixmaps->size())
		frame = 0;

	setPixmap(pixmaps->at(frame));
	animationTimer->setInterval(interval->at(frame));
	frame++;


	if(rounds > 0 ){
		rounds--;
	}


}

void KynaPixmapItem::talk()
{
	qDebug() << frame;
}

KynaPixmapItem::~ KynaPixmapItem()
{
	if(animationTimer)
	animationTimer->stop();
}

