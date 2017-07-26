#include "EnemyPurpleZombie.h"

static const int CHIP_SIZE = 64;
static const int WAIT_ANIM_TIME = 5;

EnemyPurpleZombie::EnemyPurpleZombie( const Vector& pos ) :
Enemy( pos, CHIP_SIZE ) {
}


EnemyPurpleZombie::~EnemyPurpleZombie( ) {
}

void EnemyPurpleZombie::getChipIndex( int& cx, int& cy ) const {
	const int ANIM[ ] = {
		0, 1, 2, 1
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	cx = ANIM[ ( int )getPos( ).x / WAIT_ANIM_TIME % anim_size ];
	cy = 64;
}

void EnemyPurpleZombie::act( ) {
}

