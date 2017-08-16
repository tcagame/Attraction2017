#include "EnemyNoNeckGhost.h"

static const int WAIT_ANIM_TIME = 5;
static const int MAX_HP = 3;

EnemyNoNeckGhost::EnemyNoNeckGhost( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP, false ) {
	setRadius( 36 );
}


EnemyNoNeckGhost::~EnemyNoNeckGhost( ) {
}

void EnemyNoNeckGhost::act( ) {

}

Chip EnemyNoNeckGhost::getChip( ) const {
	const int ANIM[ ] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	Chip chip = Chip( );
	chip.tx = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ] * 64;
	chip.ty = 10 * 64;
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