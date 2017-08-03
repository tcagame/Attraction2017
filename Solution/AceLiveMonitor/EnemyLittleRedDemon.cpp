#include "EnemyLittleRedDemon.h"

const int WAIT_ANIM_TIME = 6;

EnemyLittleRedDemon::EnemyLittleRedDemon( const Vector& pos ):
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE ) {
}


EnemyLittleRedDemon::~EnemyLittleRedDemon( ) {
}

Chip EnemyLittleRedDemon::getChip( ) const {
	Chip chip = Chip( );
	Vector pos = getPos( );
	chip.size = getChipSize( );
	chip.sx1 = ( int )pos.x - chip.size / 2;
	chip.sy1 = ( int )pos.y - chip.size;
	chip.sx2 = chip.sx1 + chip.size;
	chip.sy2 = chip.sy1 + chip.size;
	
	const int ANIM[ ] = {
		6, 7, 8, 9, 10, 11
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	int cx = ANIM[ ( getActCount( ) / WAIT_ANIM_TIME ) % anim_size ];
	chip.tx = cx * chip.size;
	chip.ty = 320;
	return chip;
}

void EnemyLittleRedDemon::act( ) {
	setVec( Vector( -3, 0 ) );
}

