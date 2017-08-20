#include "EnemyLittleRedDaemon.h"

static const int WAIT_ANIM_TIME = 6;
static const int MAX_HP = 3;

EnemyLittleRedDaemon::EnemyLittleRedDaemon( const Vector& pos ):
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP ) {
}


EnemyLittleRedDaemon::~EnemyLittleRedDaemon( ) {
}

Chip EnemyLittleRedDaemon::getChip( ) const {
	Chip chip = Chip( );
	Vector pos = getPos( );
	chip.size = getChipSize( );
	chip.sx1 = ( int )pos.x - chip.size / 2;
	chip.sy1 = ( int )pos.y - chip.size;
	chip.sx2 = chip.sx1 + chip.size;
	chip.sy2 = chip.sy1 + chip.size;
	
	const int ANIM[ ] = {
		9, 10, 11, 12, 13, 14
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	int cx = ANIM[ ( getActCount( ) / WAIT_ANIM_TIME ) % anim_size ];
	chip.tx = cx * chip.size;
	chip.ty = 320;
	return chip;
}

void EnemyLittleRedDaemon::act( ) {
	setVec( Vector( -3, 0 ) );
}

