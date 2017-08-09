#include "EnemyBossBloodDemon.h"

const int WAIT_ANIM_TIME = 10;

EnemyBossBloodDemon::EnemyBossBloodDemon( const Vector& pos ) :
EnemyBoss( pos, BIG_CHAR_GRAPH_SIZE ) {
}


EnemyBossBloodDemon::~EnemyBossBloodDemon( ) {
}

void EnemyBossBloodDemon::act( ) {

}

Chip EnemyBossBloodDemon::getChip( ) const {
	Chip chip = Chip( );
	Vector pos = getPos( );
	chip.size = getChipSize( );
	chip.sx1 = ( int )pos.x - chip.size / 2;
	chip.sy1 = ( int )pos.y - chip.size;
	chip.sx2 = chip.sx1 + chip.size;
	chip.sy2 = chip.sy1 + chip.size;
	
	const int ANIM[ ] = {
		0, 1, 2, 3
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	int cx = ANIM[ ( getActCount( ) / WAIT_ANIM_TIME ) % anim_size ];
	//int cy = 2;
	chip.tx = cx * chip.size;
	chip.ty = 0;
	return chip;
}