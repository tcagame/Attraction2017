#include "EnemyArcher.h"

const int WAIT_ANIM_TIME = 5;
const int MAX_HP = 0;
const int MOVE_SPEED = -2;
const int MOVE_TIME = WAIT_ANIM_TIME * 12;
const int ANIM_LOOP_TIME = WAIT_ANIM_TIME * 21;

EnemyArcher::EnemyArcher( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP ),
_act( ACTION_MOVE ) {
	setRadius( 36 );
}

EnemyArcher::~EnemyArcher( ) {
}

void EnemyArcher::act( ) {
	setVec( Vector( MOVE_SPEED, getVec( ).y ) );
	if ( ( getActCount( ) % ANIM_LOOP_TIME ) >= MOVE_TIME ) {
		setVec( Vector( ) );
	}
}

Chip EnemyArcher::getChip( ) const {
	Chip chip = Chip( );
	int ANIM[ ] = { /*move*/ 0, 1, 2, 1, 0, 1, 2, 1, 0, 1, 2, 1, /*shot*/ 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	chip.tx = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ] * 64;
	chip.ty = 13 * 64;
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