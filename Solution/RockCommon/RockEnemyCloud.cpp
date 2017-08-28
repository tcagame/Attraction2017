#include "RockEnemyCloud.h"
#include "RockStorage.h"
#include "RockItemMoney.h"

const int HP = 20;

RockEnemyCloud::RockEnemyCloud( const Vector& pos ) :
RockEnemy( pos, DOLL_CLOUD, HP, 1, 10, 10, false, true ) {
}


RockEnemyCloud::~RockEnemyCloud( ) {
}

void RockEnemyCloud::act( ) {

}

double RockEnemyCloud::getAnimTime( ) const {
	return 0;
}

void RockEnemyCloud::dropItem( ) {
	RockStorage::getTask( )->addItem( RockItemPtr( new RockItemMoney( getPos( ) + Vector( 0, getRadius( ), 0 ), RockItemMoney::MONEY_VALUE_3 ) ) );
}