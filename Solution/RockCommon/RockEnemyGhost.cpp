#include "RockEnemyGhost.h"



RockEnemyGhost::RockEnemyGhost( const Vector& pos ) :
RockEnemy( pos, DOLL_GHOST, 3, 1, 10, 10, false, false ) {
}


RockEnemyGhost::~RockEnemyGhost( ) {
}

void RockEnemyGhost::act( ) {
	setVec( ( Vector( 0, 40, 0 ) - getPos( ) ).normalize( ) );
}

double RockEnemyGhost::getAnimTime( ) const {
	return 0;
}