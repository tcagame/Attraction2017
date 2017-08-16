#include "EnemyWind.h"

static const int WAIT_ANIM_TIME = 5;
static const int GRAPH_WIDTH_NUM = 10;
static const int MAX_HP = 6;

EnemyWind::EnemyWind( const Vector& pos ) :
Enemy( pos, BIG_CHAR_GRAPH_SIZE, MAX_HP, false ) {
	setRadius( 48 );
}


EnemyWind::~EnemyWind( ) {
}

void EnemyWind::act( ) {
}

Chip EnemyWind::getChip( ) const {
	const int ANIM[ ] = {
		20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	Chip chip = Chip( );
	chip.tx = ( ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ] % GRAPH_WIDTH_NUM ) * 128;
	chip.ty = ( ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ] / GRAPH_WIDTH_NUM ) * 128;
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
