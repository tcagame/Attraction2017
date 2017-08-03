#include "EnemyPurpleZombie.h"
#include "ace_define.h"

static const int WAIT_ANIM_TIME = 5;

EnemyPurpleZombie::EnemyPurpleZombie( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE ) {
	setRadius( 36 );
}


EnemyPurpleZombie::~EnemyPurpleZombie( ) {
}

Chip EnemyPurpleZombie::getChip( ) const {
	const int ANIM[ ] = {
		0, 1, 2, 3, 4, 5
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	int cx = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ];
	int cy = 3;

	Chip chip = Chip( );
	chip.size = getChipSize( );
	chip.tx = cx * 64;
	chip.ty = cy * 64;

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

void EnemyPurpleZombie::act( ) {
}

