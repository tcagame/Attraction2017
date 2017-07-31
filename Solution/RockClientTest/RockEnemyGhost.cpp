#include "RockEnemyGhost.h"



RockEnemyGhost::RockEnemyGhost( const Vector& pos ) :
RockEnemy( pos, DOLL_GHOST ) {
}


RockEnemyGhost::~RockEnemyGhost( ) {
}

void RockEnemyGhost::act( ) {
	setVec( Vector( 0.6, -0.3, 1 ) );
}