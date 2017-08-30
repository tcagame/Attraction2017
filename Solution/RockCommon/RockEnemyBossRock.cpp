#include "RockEnemyBossRock.h"
#include "RockStorage.h"
#include "RockItemMoney.h"
#include "RockItemRock.h"
#include "RockItemBubble.h"

const int HP = 50;

RockEnemyBossRock::RockEnemyBossRock( const Vector& pos ) :
RockEnemyBoss( pos, DOLL_BOSS_ROCK, HP, 1, 10, 10, true, true ) {
}


RockEnemyBossRock::~RockEnemyBossRock( ) {
}

void RockEnemyBossRock::act( ) {

}

double RockEnemyBossRock::getAnimTime( ) const {
	return 0;
}

void RockEnemyBossRock::dropItem( ) {
	RockStoragePtr storage( RockStorage::getTask( ) );
	storage->addDropItem( RockItemPtr( new RockItemRock( getPos( ) + Vector( 0, getRadius( ), 0 ) ) ) );
	storage->addDropItem( RockItemPtr( new RockItemBubble( getPos( ) + Vector( 0, getRadius( ), 0 ) ) ) );
	
}
