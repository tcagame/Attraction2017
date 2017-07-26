#include "EnemyPurpleZombie.h"
#include "ace_define.h"

static const int WAIT_ANIM_TIME = 5;

EnemyPurpleZombie::EnemyPurpleZombie( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE ) {
}


EnemyPurpleZombie::~EnemyPurpleZombie( ) {
}

Chip EnemyPurpleZombie::getChip( ) const {
	const int ANIM[ ] = {
		0, 1, 2, 1
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	int cx = ANIM[ ( int )getPos( ).x / WAIT_ANIM_TIME % anim_size ];
	int cy = 64;

	Chip chip = Chip( );
	chip.size = getChipSize( );
	chip.tx = cx;
	chip.ty = cy;

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

