#include "EnemyHugDemon.h"

static const int WAIT_ANIM_TIME = 5;
static const int POWER = 3;

EnemyHugDemon::EnemyHugDemon( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, POWER ) {
	setRadius( 36 );
}


EnemyHugDemon::~EnemyHugDemon( ) {
}

void EnemyHugDemon::act( ) {

}

Chip EnemyHugDemon::getChip( ) const {
	const int ANIM[ ] = {
		13, 14, 15, 14
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	Chip chip = Chip( );
	chip.tx = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ] * 64;
	chip.ty = 9 * 64;
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