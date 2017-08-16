#include "EnemyTreeNuts.h"

static const int WAIT_ANIM_TIME = 5;
static const int FADE_IN_TIME = WAIT_ANIM_TIME * 9;
static const int MAX_HP = 2;

EnemyTreeNuts::EnemyTreeNuts( const Vector& pos ) :
Enemy( pos, SMALL_CHAR_GRAPH_SIZE, MAX_HP, false ),
_act( ACTION_FADE_IN ) {
	setRadius( 18 );
}

EnemyTreeNuts::~EnemyTreeNuts( ) {
}

void EnemyTreeNuts::act( ) {
	switch ( _act ) {
	case ACTION_FADE_IN:
		if ( getActCount( ) > FADE_IN_TIME ) {
			_act = ACTION_MOVE;
		}
		break;
	case ACTION_MOVE:
		setVec( Vector( -5, 0 ) );
		break;
	}
}

Chip EnemyTreeNuts::getChip( ) const {
	Chip chip = Chip( );
	switch ( _act ) {
	case ACTION_FADE_IN:
	{
		const int ANIM[ ] = { 0, 1, 2, 3, 4, 5, 6, 7, 6 };
		int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
		chip.tx = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ] * SMALL_CHAR_GRAPH_SIZE;
	}
		break;
	case ACTION_MOVE:
	{
		const int ANIM[ ] = { 5, 6, 7, 6 };
		int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
		chip.tx = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ] * SMALL_CHAR_GRAPH_SIZE;
	}
		break;
	}
	chip.ty = 2 * SMALL_CHAR_GRAPH_SIZE;
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