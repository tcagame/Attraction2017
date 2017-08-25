#include "RockEnemyWaterGhost.h"
#include "RockStorage.h"
#include "RockItemMoney.h"

const int HP = 20;

RockEnemyWaterGhost::RockEnemyWaterGhost( const Vector& pos ) :
RockEnemy( pos, DOLL_WATERGHOST, HP, 1, 10, 10, true, true ) {
}


RockEnemyWaterGhost::~RockEnemyWaterGhost( ) {
}

void RockEnemyWaterGhost::act( ) {

}

double RockEnemyWaterGhost::getAnimTime( ) const {
	return 0;
}

void RockEnemyWaterGhost::dropItem( ) {
	RockStorage::getTask( )->addItem( RockItemPtr( new RockItemMoney( getPos( ) + Vector( 0, getRadius( ), 0 ), RockItemMoney::MONEY_VALUE_3 ) ) );
}