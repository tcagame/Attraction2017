#include "RockEnemyRedBard.h"

RockEnemyRedBard::RockEnemyRedBard( const Vector& pos ) :
RockEnemy( pos, DOLL_REDBARD ) {
}


RockEnemyRedBard::~RockEnemyRedBard( ) {
}

void RockEnemyRedBard::act( ) {
	setVec( Vector( 3, 0, 5 ) );
}
