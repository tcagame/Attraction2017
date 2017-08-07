#include "EnemyBossMonsteTreer.h"

EnemyBossMonsteTreer::EnemyBossMonsteTreer( const Vector& pos ) :
EnemyBoss( pos, BIG_CHAR_GRAPH_SIZE ) {
}


EnemyBossMonsteTreer::~EnemyBossMonsteTreer( ) {
}

void EnemyBossMonsteTreer::act( ) {
}

Chip EnemyBossMonsteTreer::getChip( ) const {
	Chip chip = Chip( );
	Vector pos = getPos( );
	chip.size = 192;
	chip.sx1 = ( int )pos.x - chip.size / 2;
	chip.sy1 = ( int )pos.y - chip.size;
	chip.sx2 = chip.sx1 + chip.size;
	chip.sy2 = chip.sy1 + chip.size;
	chip.tx = 0;
	chip.ty = 128;
	return chip;
}
