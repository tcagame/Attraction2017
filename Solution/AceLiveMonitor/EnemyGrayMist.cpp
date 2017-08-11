#include "EnemyGrayMist.h"

const int WAIT_ANIM_TIME = 5;

EnemyGrayMist::EnemyGrayMist( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, false ) {
	setRadius( 36 );
}


EnemyGrayMist::~EnemyGrayMist( ) {
}

void EnemyGrayMist::act( ) {

}

Chip EnemyGrayMist::getChip( ) const {
	const int ANIM[ ] = {
		11, 12, 13, 14, 15, 16, 15, 14, 13, 12
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	Chip chip = Chip( );
	chip.tx = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ] * 64;
	chip.ty = 7 * 64;
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