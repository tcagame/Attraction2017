#include "EnemyGhoul.h"

const int WAIT_ANIM_TIME = 5;
const int MAX_HP = 3;
const int MOVE_SPEED = 1;
const int MOVE_RANGE = 25;

EnemyGhoul::EnemyGhoul( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP ),
_origin_pos( pos ) {
	setVec( Vector( MOVE_SPEED, 0 ) );
}


EnemyGhoul::~EnemyGhoul( ) {
}

void EnemyGhoul::act( ) {
	Vector vec = getVec( );
	Vector diff = getPos( ) - _origin_pos;
	if ( diff.getLength( ) > MOVE_RANGE ) {
		if ( getDir( ) == DIR_RIGHT ) {
			vec.x *= -1;
			setVec( vec );
		}
		if ( getDir( ) == DIR_LEFT ) {
			vec.x *= -1;
			setVec( vec );
		}
	}
}

Chip EnemyGhoul::getChip( ) const {
	const int ANIM[ ] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	Chip chip = Chip( );
	chip.tx = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ] * 64;
	chip.ty = 1 * 64;
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