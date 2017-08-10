#include "EnemySeed.h"

#include "Military.h"

const int WAIT_ANIM_TIME = 5;
const int ATTACK_TIME = WAIT_ANIM_TIME * 11;
const int JUMP_POWER = -15;

EnemySeed::EnemySeed( const Vector& pos ) :
Enemy( pos, SMALL_CHAR_GRAPH_SIZE ) {
	setRadius( 16 );
	setVec( Vector( -10, 0 ) );
}

EnemySeed::~EnemySeed( ) {
}

void EnemySeed::act( ) {
	if ( isStanding( ) ) setVec( getVec( ) + Vector( 0, JUMP_POWER ) );
}

Chip EnemySeed::getChip( ) const {
	Chip chip = Chip( );
	chip.tx = 0 * 32 + 10 * 64;
	if ( isStanding( ) ) {
		chip.tx += 32;
	}
	chip.ty = 4 * 64;
	chip.size = getChipSize( );
	Vector pos = getPos( );
	chip.sx1 = ( int )pos.x - chip.size / 2;
	chip.sy1 = ( int )pos.y - chip.size;
	chip.sx2 = chip.sx1 + chip.size;
	chip.sy2 = chip.sy1 + chip.size;
	return chip;
}