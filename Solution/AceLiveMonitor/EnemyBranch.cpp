#include "EnemyBranch.h"

const int WAIT_ANIM_TIME = 5;

EnemyBranch::EnemyBranch( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, false ) {
	setRadius( 36 );
}

EnemyBranch::~EnemyBranch( ) {
}

void EnemyBranch::act( ) {
}

Chip EnemyBranch::getChip( ) const {
	Chip chip = Chip( );
	const int ANIM[ ] = { 0, 1, 2, 3, 4, 5, 6, 3, 2, 1, 0  };
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	chip.tx = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ] * 64 + 3 * 64;
	chip.ty = 4 * 64;
	chip.size = getChipSize( );
	Vector pos = getPos( );
	chip.sx1 = ( int )pos.x - chip.size / 2;
	chip.sy1 = ( int )pos.y - chip.size;
	chip.sx2 = chip.sx1 + chip.size;
	chip.sy2 = chip.sy1 + chip.size;
	return chip;
}