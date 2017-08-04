#include "RockEnemyGhost.h"



RockEnemyGhost::RockEnemyGhost( const Vector& pos ) :
RockEnemy( pos, DOLL_GHOST, false ) {
}


RockEnemyGhost::~RockEnemyGhost( ) {
}

void RockEnemyGhost::act( ) {
	setVec( Vector( 0.6, 0, 1 ) );
}

double RockEnemyGhost::getAnimTime( ) const {
	return 0;
}