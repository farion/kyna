#include "kynasettingsreader.h"

#include "kynalevel.h"
#include "kynaunit.h"
#include "kynafield.h"

KynaSettingsReader::KynaSettingsReader()
{
}

LevelSettings KynaSettingsReader::readLevel ( QString levelname )
{
	LevelSettings settings;
	loadLevelFile ( &settings, levelname + ".xml" );

	for ( int i = 0; i < settings.units->size(); i ++ )
	{
		loadUnitFile ( settings.units->at ( i ),settings.units->at ( i )->race + ".xml" );
	}



	return settings;

}

void  KynaSettingsReader::loadLevelFile ( LevelSettings *settings, QString filename )
{
	QDomDocument doc;

	QFile file ( filename );

	if ( !file.open ( QIODevice::ReadOnly ) )
	{
		qDebug() << "XML not found " << filename;
		return ;
	}

	if ( !doc.setContent ( &file ) )
	{
		qDebug() << "no XML-Content";
		file.close();
		return ;
	}

	file.close();



	settings->tilenames = new QMap<int,QString>;

	settings->units = new QList<UnitSettings*>;

	QDomElement docElem = doc.documentElement();

	QDomNode n = docElem.firstChild();

	for ( QDomNode n = docElem.firstChild(); !n.isNull(); n = n.nextSibling() )
	{
		QDomElement e = n.toElement();

		if ( !e.isNull() )
		{

			if ( e.tagName() == "level" )
			{
				parseLevelNode ( &e,settings );

			}
		}
	}

	return;
}

void  KynaSettingsReader::loadUnitFile ( UnitSettings *settings, QString filename )
{
	QDomDocument doc;

	QFile file ( filename );

	if ( !file.open ( QIODevice::ReadOnly ) )
	{
		qDebug() << "XML not found " << filename;
		return ;
	}

	if ( !doc.setContent ( &file ) )
	{
		qDebug() << "no XML-Content";
		file.close();
		return ;
	}

	file.close();


	QDomElement docElem = doc.documentElement();

	QDomNode n = docElem.firstChild();

	for ( QDomNode n = docElem.firstChild(); !n.isNull(); n = n.nextSibling() )
	{
		QDomElement e = n.toElement();

		if ( !e.isNull() )
		{

			if ( e.tagName() == "unit" )
			{

				settings->movespeed = e.attribute ( "movespeed" ).toInt();
				for ( QDomNode n = e.firstChild(); !n.isNull(); n = n.nextSibling() )
				{
					QDomElement e = n.toElement();

					if ( !e.isNull() )
					{
						if ( e.tagName() == "tiles" )
						{
							for ( QDomNode n = e.firstChild(); !n.isNull(); n = n.nextSibling() )
							{
								QDomElement e = n.toElement();

								if ( !e.isNull() )
								{

									if ( e.tagName() == "left" )
									{
										for ( QDomNode n = e.firstChild(); !n.isNull(); n = n.nextSibling() )
										{
											QDomElement e = n.toElement();

											if ( !e.isNull() )
											{
												if ( e.tagName() == "tile" )
												{
													settings->lefttiles->append ( e.attribute ( "file" ) );
												}
											}
										}
									}

									else if ( e.tagName() == "right" )
									{
										for ( QDomNode n = e.firstChild(); !n.isNull(); n = n.nextSibling() )
										{
											QDomElement e = n.toElement();

											if ( !e.isNull() )
											{
												if ( e.tagName() == "tile" )
												{
													settings->righttiles->append ( e.attribute ( "file" ) );
												}
											}
										}
									}

									else if ( e.tagName() == "top" )
									{
										for ( QDomNode n = e.firstChild(); !n.isNull(); n = n.nextSibling() )
										{
											QDomElement e = n.toElement();

											if ( !e.isNull() )
											{
												if ( e.tagName() == "tile" )
												{
													settings->toptiles->append ( e.attribute ( "file" ) );
												}
											}
										}
									}

									else if ( e.tagName() == "down" )
									{
										for ( QDomNode n = e.firstChild(); !n.isNull(); n = n.nextSibling() )
										{
											QDomElement e = n.toElement();

											if ( !e.isNull() )
											{
												if ( e.tagName() == "tile" )
												{
													settings->downtiles->append ( e.attribute ( "file" ) );
												}
											}
										}
									}
									else if ( e.tagName() == "dead" )
									{
										for ( QDomNode n = e.firstChild(); !n.isNull(); n = n.nextSibling() )
										{
											QDomElement e = n.toElement();

											if ( !e.isNull() )
											{
												if ( e.tagName() == "tile" )
												{
													settings->deadtiles->append ( e.attribute ( "file" ) );
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	return;

}

void KynaSettingsReader::parseLevelNode ( QDomElement * e, LevelSettings * settings )
{

	settings->fill = e->attribute ( "fill" ).toInt();
	settings->levelname = e->attribute ( "name" );
	settings->width = e->attribute ( "width" ).toInt();
	settings->fieldset = e->attribute ( "fieldset" );
	settings->height = e->attribute ( "height" ).toInt();
	settings->minPlayer = e->attribute ( "minPlayer" ).toInt();
	settings->maxPlayer = e->attribute ( "maxPlayer" ).toInt();

	for ( QDomNode n = e->firstChild(); !n.isNull(); n = n.nextSibling() )
	{
		QDomElement e = n.toElement();

		if ( !e.isNull() )
		{
			if ( e.tagName() == "tiles" )
			{
				for ( QDomNode n = e.firstChild(); !n.isNull(); n = n.nextSibling() )
				{
					QDomElement e = n.toElement();

					if ( !e.isNull() )
					{
						if ( e.tagName() == "cornerLeftTop" )
						{
							settings->tilenames->insert ( FIELD_WALL_CORNER_LT,e.attribute ( "file" ) );
						}

						else if ( e.tagName() == "cornerLeftBottom" )
						{
							settings->tilenames->insert ( FIELD_WALL_CORNER_LB,e.attribute ( "file" ) );
						}

						else if ( e.tagName() == "cornerRightTop" )
						{
							settings->tilenames->insert ( FIELD_WALL_CORNER_RT,e.attribute ( "file" ) );
						}

						else if ( e.tagName() == "cornerRightBottom" )
						{
							settings->tilenames->insert ( FIELD_WALL_CORNER_RB,e.attribute ( "file" ) );
						}

						else if ( e.tagName() ==  "borderLeft" )
						{
							settings->tilenames->insert ( FIELD_WALL_BORDER_L,e.attribute ( "file" ) );
						}

						else if ( e.tagName() ==  "borderTop" )
						{
							settings->tilenames->insert ( FIELD_WALL_BORDER_T,e.attribute ( "file" ) );
						}

						else if ( e.tagName() ==  "borderRight" )
						{
							settings->tilenames->insert ( FIELD_WALL_BORDER_R,e.attribute ( "file" ) );
						}

						else if ( e.tagName() == "borderBottom" )
						{
							settings->tilenames->insert ( FIELD_WALL_BORDER_B,e.attribute ( "file" ) );
						}

						else if ( e.tagName() == "indestructible" )
						{
							settings->tilenames->insert ( FIELD_WALL_INDESTRUCTIBLE,e.attribute ( "file" ) );
						}

						else if ( e.tagName() ==   "destructible" )
						{
							settings->tilenames->insert ( FIELD_WALL_DESTRUCTIBLE,e.attribute ( "file" ) );
						}

						else if ( e.tagName() ==  "free" )
						{
							settings->tilenames->insert ( FIELD_FREE,e.attribute ( "file" ) );
						}
					}
				}
			}
			else if ( e.tagName() == "goodies" )
			{
				parseGoodieNode ( &e,settings );
			}
			else if ( e.tagName() == "exit" )
			{
				parseExitNode ( &e,settings );
			}
			else if ( e.tagName() == "units" )
			{
				for ( QDomNode n = e.firstChild(); !n.isNull(); n = n.nextSibling() )
				{
					QDomElement e = n.toElement();

					if ( !e.isNull() )
					{
						UnitSettings *unitsettings = new UnitSettings;
						unitsettings->name = e.attribute ( "name" );
						unitsettings->name = e.attribute ( "name" );
						unitsettings->race = e.attribute ( "race" );
						unitsettings->startX = e.attribute ( "x" ).toInt();
						unitsettings->startY = e.attribute ( "y" ).toInt();
						unitsettings->lefttiles = new QList<QString>();
						unitsettings->righttiles = new QList<QString>();
						unitsettings->toptiles = new QList<QString>();
						unitsettings->downtiles = new QList<QString>();
						unitsettings->deadtiles = new QList<QString>();

						if ( e.tagName() ==  "player" )
						{
							unitsettings->type = UNIT_TYPE_PLAYER;
						}

						else if ( e.tagName() ==   "enemy" )
						{
							unitsettings->type = UNIT_TYPE_ENEMY;
						}

						else if ( e.tagName() ==  "neutral" )
						{
							unitsettings->type = UNIT_TYPE_NEUTRAL;
						}

						settings->units->append ( unitsettings );
					}
				}
			}
		}
	}
}

void KynaSettingsReader::parseGoodieNode ( QDomElement * e, LevelSettings * settings )
{

	settings->goodies = new QList<GoodieSettings*>;


	for ( QDomNode n = e->firstChild(); !n.isNull(); n = n.nextSibling() )
	{
		QDomElement e = n.toElement();

		if ( !e.isNull() )
		{
			if ( e.tagName() == "goodie" )
			{

				GoodieSettings *goodiesettings = new GoodieSettings;
				for ( QDomNode n = e.firstChild(); !n.isNull(); n = n.nextSibling() )
				{
					QDomElement e = n.toElement();

					if ( !e.isNull() )
					{
						if ( e.tagName() == "buffs" )
						{
							parseBuffsNode ( &e,&(goodiesettings->buffs ));
						}
						else if ( e.tagName() == "tiles" )
						{
							parseTilesNode ( &e,&(goodiesettings->tiles) );
						}
					}
				}
				settings->goodies->append ( goodiesettings );
			}
		}
	}

}

void KynaSettingsReader::parseTilesNode ( QDomElement * e,QList<QString> *tilenames )
{
	for ( QDomNode n = e->firstChild(); !n.isNull(); n = n.nextSibling() )
	{
		QDomElement e = n.toElement();

		if ( !e.isNull() )
		{
			if ( e.tagName() == "tile" )
			{
				tilenames->append ( e.attribute ( "file" ) );
			}

		}
	}
}

void KynaSettingsReader::parseBuffsNode ( QDomElement * e, QMap< int, int > * buffs )
{

	for ( QDomNode n = e->firstChild(); !n.isNull(); n = n.nextSibling() )
	{
		QDomElement e = n.toElement();

		if ( !e.isNull() )
		{
			if ( e.tagName() == "buff" )
			{
				if ( e.attribute ( "type" ) == "BOMB_RANGE" )
					buffs->insert ( BUFF_BOMB_RANGE,e.attribute ( "value" ).toInt() );
				else if ( e.attribute ( "type" ) == "BOMB_COUNT" )
					buffs->insert ( BUFF_BOMB_COUNT,e.attribute ( "value" ).toInt() );
				else if ( e.attribute ( "type" ) == "MOVE_SPEED" )
					buffs->insert ( BUFF_MOVE_SPEED,e.attribute ( "value" ).toInt() );
				else if ( e.attribute ( "type" ) == "GO_THROUGH_WALLS" )
					buffs->insert ( BUFF_GO_THROUGH_WALLS,e.attribute ( "value" ).toInt() );
				else if ( e.attribute ( "type" ) == "GO_THROUGH_BOMBS" )
					buffs->insert ( BUFF_GO_THROUGH_BOMBS,e.attribute ( "value" ).toInt() );
			}

		}
	}
}

void KynaSettingsReader::parseExitNode(QDomElement * e, LevelSettings * settings)
{

	settings->exit = new ExitSettings;


	for ( QDomNode n = e->firstChild(); !n.isNull(); n = n.nextSibling() )
	{
		QDomElement e = n.toElement();

		if ( !e.isNull() )
		{
			if ( e.tagName() == "inactivetiles" )
			{
					parseTilesNode ( &e,&(settings->exit->inactivetiles) );
			}
			else if ( e.tagName() == "activetiles" )
			{
					parseTilesNode ( &e,&(settings->exit->activetiles) );
			}
		}
	}


}
