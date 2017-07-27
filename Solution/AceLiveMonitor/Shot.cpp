#include "Shot.h"

const int SHOT_SPEED = 10; 

Shot::Shot( const Vector& pos, DIR dir ) :
Character( pos, NORMAL_CHAR_GRAPH_SIZE, false ) {
	Vector vec = Vector( SHOT_SPEED, 0 );
	if ( dir == DIR_LEFT ) {
		vec.x *= -1;
	}
	setVec( vec );
}

Shot::~Shot( ) {
}

void Shot::act( ) {
}

Chip Shot::getChip( ) const {
	Vector pos = getPos( );
	Chip chip = Chip( );
	chip.tx = 64;
	chip.ty = 128;
	chip.size = getChipSize( );
	chip.sx1 = ( int )pos.x - chip.size / 2;
	chip.sx2 = chip.sx1 + chip.size;
	chip.sy1 = ( int )pos.y - chip.size;
	chip.sy2 = chip.sy1 + chip.size;
	if ( getDir( ) == DIR_RIGHT ) {
		int tmp = chip.sx1;
		chip.sx1 = chip.sx2;
		chip.sx2 = tmp;
	}
	return chip;
}