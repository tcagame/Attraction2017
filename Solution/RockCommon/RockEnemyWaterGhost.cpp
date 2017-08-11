#include "RockEnemyWaterGhost.h"

RockEnemyWaterGhost::RockEnemyWaterGhost( const Vector& pos ) :
RockEnemy( pos, DOLL_WATERGHOST, 1, 10, 10, true, true ) {
}


RockEnemyWaterGhost::~RockEnemyWaterGhost( ) {
}

void RockEnemyWaterGhost::act( ) {

}

double RockEnemyWaterGhost::getAnimTime( ) const {
	return 0;
}
