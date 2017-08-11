#include "EnemyFlog.h"

const int WAIT_ANIM_TIME = 5;

EnemyFlog::EnemyFlog( const Vector& pos ) :
Enemy( pos, SMALL_CHAR_GRAPH_SIZE ) {
	setRadius( 16 );
}


EnemyFlog::~EnemyFlog( ) {
}

void EnemyFlog::act( ) {

}

Chip EnemyFlog::getChip( ) const {
	const int ANIM[ ] = {
		0, 1, 2, 3, 4
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	Chip chip = Chip( );
	chip.tx = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ] * 32;
	chip.ty = 1 * 32;
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