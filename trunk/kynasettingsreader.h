#ifndef KYNASETTINGSREADER_H
#define KYNASETTINGSREADER_H

#include <QtXml>
#include "kynatypes.h"

class KynaLevel;
class KynaField;
class KynaUnit;

class KynaSettingsReader
{
	public:
		KynaSettingsReader();
		LevelSettings  readLevel ( QString levelname );
		UnitSettings  readUnit ( QString unitname );

	private:
		void loadLevelFile (  LevelSettings *settings,QString filename );
		void loadUnitFile ( UnitSettings *settings, QString filename );
		
		void parseLevelNode( QDomElement *e,LevelSettings *settings);

		void parseGoodieNode( QDomElement *e, LevelSettings *settings);
		void parseExitNode( QDomElement *e, LevelSettings *settings);
		void parseTilesNode( QDomElement *e, QList<QString> *tilenames);
		void parseBuffsNode( QDomElement *e, QMap<int,int> *buffs);
};

#endif
