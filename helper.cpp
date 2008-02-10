#include <QKeyEvent>

#include "helper.h"

int getTileForFieldType ( int fieldType )
{
	return fieldType;
}

QString getNameForTile ( int tileNo )
{
	QString name;

	switch ( tileNo )
	{
		case TILES_LEVEL_CORNER_LT:
			name.append ( "wand_lt" );
			break;
		case TILES_LEVEL_CORNER_LB:
			name.append ( "wand_lb" );
			break;
		case TILES_LEVEL_CORNER_RT:
			name.append ( "wand_rt" );
			break;
		case TILES_LEVEL_CORNER_RB:
			name.append ( "wand_rb" );
			break;
		case TILES_LEVEL_BORDER_L:
			name.append ( "wand_l" );
			break;
		case TILES_LEVEL_BORDER_T:
			name.append ( "wand_t" );
			break;
		case TILES_LEVEL_BORDER_R:
			name.append ( "wand_r" );
			break;
		case TILES_LEVEL_BORDER_B:
			name.append ( "wand_b" );
			break;
		case TILES_LEVEL_INDESTRUCTIBLE:
			name.append ( "saeule" );
			break;
		case TILES_LEVEL_DESTRUCTIBLE:
			name.append ( "mauer" );
			break;
		case TILES_LEVEL_FREE:
			name.append ( "gras" );
			break;
		case TILES_LEVEL_SHADOW_LT:
			name.append ( "shadow_lt" );
			break;
		case TILES_LEVEL_SHADOW_L:
			name.append ( "shadow_l" );
			break;
		case TILES_LEVEL_SHADOW_LTI:
			name.append ( "shadow_lti" );
			break;
		case TILES_LEVEL_SHADOW_LIT:
			name.append ( "shadow_lit" );
			break;
		case TILES_LEVEL_SHADOW_LI:
			name.append ( "shadow_li" );
			break;
		case TILES_PLAYER_UP:
			name.append ( "player_hinten" );
			break;
		case TILES_PLAYER_LEFT:
			name.append ( "player_left" );
			break;
		case TILES_PLAYER_RIGHT:
			name.append ( "player_right" );
			break;
		case TILES_PLAYER_DOWN:
			name.append ( "player" );
			break;
		case TILES_BALLOON_UP:
			name.append ( "balloon_up");
			break;
		case TILES_BALLOON_LEFT:
			name.append ( "balloon_left" );
			break;
		case TILES_BALLOON_RIGHT:
			name.append ( "balloon_right" );
			break;
		case TILES_BALLOON_DOWN:
			name.append ( "balloon_down" );
			break;
		case TILES_ITEMS_BOMB:
			name.append ( "bomb" );
			break;
		case TILES_EXPLODE_BOMB_C:
			name.append ( "explode_c" );
			break;
		case TILES_EXPLODE_BOMB_V:
			name.append ( "explode_v" );
			break;
		case TILES_EXPLODE_BOMB_H:
			name.append ( "explode_h" );
			break;
		case TILES_EXPLODE_BOMB_EL:
			name.append ( "explode_el" );
			break;
		case TILES_EXPLODE_BOMB_ER:
			name.append ( "explode_er" );
			break;
		case TILES_EXPLODE_BOMB_EB:
			name.append ( "explode_eb" );
			break;
		case TILES_EXPLODE_BOMB_ET:
			name.append ( "explode_et" );
			break;
		default:
			name.append ( "default" );
	}

	name.append ( "." );
	name.append ( TILES_TYPE );
	return name;
}
