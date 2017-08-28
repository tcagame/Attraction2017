#include "RockEnemyBossRcok.h"
#include "RockStorage.h"
#include "RockItemMoney.h"
#include "RockItemRock.h"

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
	RockStoragePtr storage( RockStorage::getTask( ) );
	//storage->addItem( RockItemPtr( new RockItemMoney( getPos( ) + Vector( 0, getRadius( ), 0 ), RockItemMoney::MONEY_VALUE_3 ) ) );
	storage->addItem( RockItemPtr( new RockItemRock( getPos( ) + Vector( 0, getRadius( ), 0 ) ) ) );
}