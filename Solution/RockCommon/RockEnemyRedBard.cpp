#include "RockEnemyRedBard.h"
#include "RockStorage.h"
#include "RockItemMoney.h"

const int HP = 30;

RockEnemyRedBard::RockEnemyRedBard( const Vector& pos ) :
RockEnemy( pos, DOLL_REDBARD, HP, 1, 10, 10, false, true ) {
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

void RockEnemyRedBard::dropItem( ) {
	RockStorage::getTask( )->addDropItem( RockItemPtr( new RockItemMoney( getPos( ) + Vector( 0, getRadius( ), 0 ), RockItemMoney::MONEY_VALUE_1 ) ) );
}