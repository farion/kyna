#define PX_MULTI			1
#define BOX_LENGTH		48
#define UNIT_LENGTH		80
#define SHADOW_WIDTH		0

/* Abstand zum Rand */
#define BORDER		18

/* darf BORDER nicht ueberschreiten */
#define MOVE_ACC							4

#define TILES_PATH 						"data/tileset"
#define LEVELS_PATH 						"data/levels"
#define UNITS_PATH 						"data/units"
#define DEFAULT_TILESET					"default"

#define KEY_LEFT							0
#define KEY_RIGHT							1
#define KEY_UP								2
#define KEY_DOWN							3
#define KEY_BOMB							4
#define KEY_FIRE							5


/* buff types */

#define BUFF_DUMMY						0

/* permanent buffs */
#define BUFF_BOMB_RANGE					1
#define BUFF_BOMB_COUNT					2
#define BUFF_MOVE_SPEED					3

/* volatile buffs */
#define BUFF_GO_THROUGH_WALLS			4
//needed ?
#define BUFF_GO_THROUGH_UNITS			5
#define BUFF_GO_THROUGH_BOMBS			6


/* unit types */
#define UNIT_TYPE_PLAYER				1
#define UNIT_TYPE_ENEMY					2
#define UNIT_TYPE_NEUTRAL				3

/* Control types */
#define CTRL_TYPE_KEYBOARD_1			1
#define CTRL_TYPE_KEYBOARD_2			2
#define CTRL_TYPE_KEYBOARD_3			3
#define CTRL_TYPE_KEYBOARD_4			4
#define CTRL_TYPE_KI_RANDOM			5
#define CTRL_TYPE_NETWORK				6 
//TODO If Network is really working, i will - as we in germany do - "ein Fass aufmachen"

/* kinds of fields */
#define FIELD_WALL_CORNER_LT			0
#define FIELD_WALL_CORNER_LB			1
#define FIELD_WALL_CORNER_RT			2
#define FIELD_WALL_CORNER_RB			3
#define FIELD_WALL_BORDER_L			4
#define FIELD_WALL_BORDER_T			5
#define FIELD_WALL_BORDER_R			6
#define FIELD_WALL_BORDER_B			7
#define FIELD_WALL_INDESTRUCTIBLE	8
#define FIELD_WALL_DESTRUCTIBLE		9
#define FIELD_FREE						10



/* Tiles for Level  -- obsolte TODO */

/* Wird als Dateiendung benutzt */
#define TILES_TYPE						"png"

#define TILES_COUNT						34

#define TILES_LEVEL_CORNER_LT			0
#define TILES_LEVEL_CORNER_LB			1
#define TILES_LEVEL_CORNER_RT			2
#define TILES_LEVEL_CORNER_RB			3
#define TILES_LEVEL_BORDER_L			4
#define TILES_LEVEL_BORDER_T			5
#define TILES_LEVEL_BORDER_R			6
#define TILES_LEVEL_BORDER_B			7
#define TILES_LEVEL_INDESTRUCTIBLE	8
#define TILES_LEVEL_DESTRUCTIBLE		9
#define TILES_LEVEL_FREE				10
#define TILES_LEVEL_SHADOW_LT			11
#define TILES_LEVEL_SHADOW_L			12
#define TILES_LEVEL_SHADOW_T			13
#define TILES_LEVEL_SHADOW_LTI		14
#define TILES_LEVEL_SHADOW_LIT		15
#define TILES_LEVEL_SHADOW_LI			16
#define TILES_LEVEL_SHADOW_TI			17

#define TILES_PLAYER_UP					18
#define TILES_PLAYER_LEFT				19
#define TILES_PLAYER_RIGHT				20
#define TILES_PLAYER_DOWN				21

#define TILES_BALLOON_UP				22
#define TILES_BALLOON_LEFT				23
#define TILES_BALLOON_RIGHT			24
#define TILES_BALLOON_DOWN				25

#define TILES_ITEMS_BOMB				26

#define TILES_EXPLODE_BOMB_C			27
#define TILES_EXPLODE_BOMB_V			28
#define TILES_EXPLODE_BOMB_H			29
#define TILES_EXPLODE_BOMB_EL			30
#define TILES_EXPLODE_BOMB_ER			31
#define TILES_EXPLODE_BOMB_EB			32
#define TILES_EXPLODE_BOMB_ET			33


#define OBJ_FIELD					0
#define OBJ_UNIT					1

/* KI */
#define	NORTH						0
#define	EAST						1
#define	SOUTH						3
#define	WEST						2


/* Bei mehreren Items pro ZINDEX wird addiert, also sollte der zwischenraum ausreichend sein */
#define ZINDEX_OVERLAY					200000
#define ZINDEX_PLAYER 					110000
#define ZINDEX_KI 						60000
#define ZINDEX_FIELD_BORDER			50000
#define ZINDEX_FIELD_FREE				10000
#define ZINDEX_FIELD_WALL				30000
#define ZINDEX_BOMB						70000
#define ZINDEX_GOODIE					20000

/* Bomb Settings */
#define BOMB_FIRE_TIME					40


#define FIRE_WAY_STOP			0
#define FIRE_WAY_CONTINUE		1

#define MODE_BOMB_DONOTHING	0
#define MODE_BOMB_EXPLODED		1
#define MODE_BOMB_TICKS 		2

#define MODE_UNIT_DEAD			2

#define MODE_EXIT_INACTIVE		1
#define MODE_EXIT_ACTIVE		2
