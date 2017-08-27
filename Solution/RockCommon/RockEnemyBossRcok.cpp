#include "RockEnemyBossRcok.h"
#include "RockStorage.h"
#include "RockItemMoney.h"

const int HP = 50;

RockEnemyBossRcok::RockEnemyBossRcok( const Vector& pos ) :
RockEnemy( pos, DOLL_BOSS_ROCK, HP, 1, 10, 10, true, true ) {
}


RockEnemyBossRcok::~RockEnemyBossRcok( ) {
}

void RockEnemyBossRcok::act( ) {

}

double RockEnemyBossRcok::getAnimTime( ) const {
	return 0;
}

void RockEnemyBossRcok::dropItem( ) {
	RockStorage::getTask( )->addItem( RockItemPtr( new RockItemMoney( getPos( ) + Vector( 0, getRadius( ), 0 ), RockItemMoney::MONEY_VALUE_3 ) ) );
}