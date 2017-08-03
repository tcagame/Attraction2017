#include "EnemyBossRedDemon.h"

const int WAIT_ANIM_TIME = 10;

EnemyBossRedDemon::EnemyBossRedDemon( const Vector& pos ) :
EnemyBoss( pos, BIG_CHAR_GRAPH_SIZE ) {
}


EnemyBossRedDemon::~EnemyBossRedDemon( ) {
}

void EnemyBossRedDemon::act( ) {
}

Chip EnemyBossRedDemon::getChip( ) const {
	Chip chip = Chip( );
	Vector pos = getPos( );
	chip.size = getChipSize( );
	chip.sx1 = ( int )pos.x - chip.size / 2;
	chip.sy1 = ( int )pos.y - chip.size;
	chip.sx2 = chip.sx1 + chip.size;
	chip.sy2 = chip.sy1 + chip.size;
	
	const int ANIM[ ] = {
		0, 1
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	int cx = ANIM[ ( getActCount( ) / WAIT_ANIM_TIME ) % anim_size ];
	//int cy = 2;
	chip.tx = cx * chip.size;
	chip.ty = 320;
	return chip;
}

Chip EnemyBossRedDemon::getChip2( ) const {
	Chip chip = Chip( );
	Vector pos = getPos( );
	chip.size = getChipSize( );
	chip.sx1 = ( int )pos.x - chip.size / 2;
	chip.sy1 = ( int )pos.y - chip.size - ( int )( sin( ( double )getActCount( ) / PI * 1 ) * 40 ) - 20;
	chip.sx2 = chip.sx1 + chip.size;
	chip.sy2 = chip.sy1 + chip.size;
	chip.tx = 2 * chip.size;
	chip.ty = 320;
	return chip;
}
