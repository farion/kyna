#ifndef KYNATYPES_H
#define KYNATYPES_H

#include <QMap>
#include <QList>
#include <QString>

typedef int boxI; /* int fuer Übergabe von Positionen und Längen relativ zu Boxen */
typedef int dirI; /* int fuer Übergabe von Positionen und Längen anhand von Bewegungsschritten/Zeichenschritten */

struct boxCoord
{
	int x;
	int y;
};

struct ExitSettings {
	QList<QString> inactivetiles;
	QList<QString> activetiles;
};

struct GoodieSettings {
	QMap<int,int> buffs;
	QList<QString> tiles;
};


struct UnitSettings {
	int type;
	QString race;
	QString name;
	boxI startX;
	boxI startY;
	int movespeed;
	QList<QString> *lefttiles;	
	QList<QString> *righttiles;	
	QList<QString> *toptiles;	
	QList<QString> *downtiles;	
	QList<QString> *deadtiles;	
};

struct LevelSettings {
	int fill;
	QString fieldset;
	QString levelname;
	boxI width;
	boxI height;
	int minPlayer;
	int maxPlayer;
	QList<UnitSettings*> *units;
	QList<GoodieSettings*> *goodies;
	ExitSettings *exit;
	QMap<int,QString> *tilenames;
};


#endif
