#include "EnemyTree.h"

static const int WAIT_ANIM_TIME = 5;

EnemyTree::EnemyTree( const Vector& pos ) :
Enemy( pos, BIG_CHAR_GRAPH_SIZE ) {
	setRadius( 36 );
}


EnemyTree::~EnemyTree( ) {
}

void EnemyTree::act( ) {

}

Chip EnemyTree::getChip( ) const {
	const int ANIM[ ] = {
		0, 1
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	Chip chip = Chip( );
	chip.tx = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ] * 128;
	chip.ty = 6 * 128;
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