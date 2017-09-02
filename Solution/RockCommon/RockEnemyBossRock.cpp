#include "RockEnemyBossRock.h"
#include "RockStorage.h"
#include "RockItemMoney.h"
#include "RockItemRock.h"
#include "RockItemBubble.h"
#include "RockFamily.h"
#include "RockPlayer.h"

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
	RockFamilyPtr family( RockFamily::getTask( ) );
	int num = 0;
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		if ( family->getPlayer( i )->isActive( ) ) {
			num++;
		}
	}
	for ( int i = 0; i < num; i++ ) {
		storage->addDropItem( RockItemPtr( new RockItemRock( getPos( ) + Vector( i * 20, getRadius( ), 0 ) ) ) );
		storage->addDropItem( RockItemPtr( new RockItemBubble( getPos( ) + Vector( i * 20, getRadius( ), 0 ) ) ) );
	}
}
