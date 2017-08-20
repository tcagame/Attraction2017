#include "EnemyArcherAttack.h"

const int MAX_HP = 2;
const Vector MOVE_SPEED( -6, 0 );

EnemyArcherAttack::EnemyArcherAttack( const Vector& pos ) :
Enemy( pos, SMALL_CHAR_GRAPH_SIZE, MAX_HP, false ) {
	setVec( MOVE_SPEED );
}

EnemyArcherAttack::~EnemyArcherAttack( ) {
}

void EnemyArcherAttack::act( ) {
}

Chip EnemyArcherAttack::getChip( ) const {
	Chip chip;
	chip.size = getChipSize( );
	chip.tx = SMALL_CHAR_GRAPH_SIZE * 6;
	chip.ty = SMALL_CHAR_GRAPH_SIZE * 1;
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
