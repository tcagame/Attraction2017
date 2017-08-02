#include "EnemyGhost.h"

const int WAIT_ANIM_TIME = 5;
const int FADE_IN_TIME = WAIT_ANIM_TIME * 2;

EnemyGhost::EnemyGhost( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, false ),
_act( ACTION_FADE_IN ) {
	setRadius( 36 );
}

EnemyGhost::~EnemyGhost( ) {
}

void EnemyGhost::act( ) {
	switch ( _act ) {
	case ACTION_FADE_IN:
		if ( getActCount( ) > FADE_IN_TIME ) {
			_act = ACTION_MOVE;
		}
		break;
	case ACTION_MOVE:
		break;
	}
}

Chip EnemyGhost::getChip( ) const {
	Chip chip = Chip( );
	switch ( _act ) {
	case ACTION_FADE_IN:
	{
		const int ANIM[ ] = { 0, 1 };
		int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
		chip.tx = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ] * 64;
	}
		break;
	case ACTION_MOVE:
	{
		const int ANIM[ ] = { 2, 3 };
		int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
		chip.tx = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ] * 64;
	}
		break;
	}
	chip.ty = 3 * 64;
	chip.size = getChipSize( );
	
	Vector pos = getPos( );
	DIR dir = getDir( );
	if ( dir == DIR_RIGHT ){
		chip.sx1 = ( int )pos.x - chip.size / 2 + chip.size;
		chip.sy1 = ( int )pos.y - chip.size;
		chip.sx2 = chip.sx1 - chip.size;
		chip.sy2 = chip.sy1 + chip.size;
	} else {
		chip.sx1 = ( int )pos.x - chip.size / 2;
		chip.sy1 = ( int )pos.y - chip.size;
		chip.sx2 = chip.sx1 + chip.size;
		chip.sy2 = chip.sy1 + chip.size;
	}
	return chip;
}