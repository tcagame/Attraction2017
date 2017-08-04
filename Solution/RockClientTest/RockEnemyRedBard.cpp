#include "RockEnemyRedBard.h"

RockEnemyRedBard::RockEnemyRedBard( const Vector& pos ) :
RockEnemy( pos, DOLL_REDBARD, false ) {
}


RockEnemyRedBard::~RockEnemyRedBard( ) {
}

void RockEnemyRedBard::act( ) {
	Vector vec = ( Vector( 0, 40, 0 ) - getPos( ) ).normalize( );
	setVec( vec );
}

double RockEnemyRedBard::getAnimTime( ) const {
	return 0;
}