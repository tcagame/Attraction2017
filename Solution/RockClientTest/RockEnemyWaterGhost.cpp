#include "RockEnemyWaterGhost.h"

RockEnemyWaterGhost::RockEnemyWaterGhost( const Vector& pos ) :
RockEnemy( pos, DOLL_WATERGHOST ) {
}


RockEnemyWaterGhost::~RockEnemyWaterGhost( ) {
}

void RockEnemyWaterGhost::act( ) {

}

double RockEnemyWaterGhost::getAnimTime( ) const {
	return 0;
}
