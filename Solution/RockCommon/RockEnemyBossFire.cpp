#include "RockEnemyBossFire.h"
#include "RockStorage.h"
#include "RockItemFire.h"
#include "RockItemBubble.h"
#include "RockFamily.h"
#include "RockPlayer.h"

const int HP = 10;

RockEnemyBossFire::RockEnemyBossFire( const Vector& pos ) :
RockEnemyBoss( pos, DOLL_GHOST, HP, 1, 10, 10, true, true ) {
}


RockEnemyBossFire::~RockEnemyBossFire( ) {
}

void RockEnemyBossFire::act( ) {

}

double RockEnemyBossFire::getAnimTime( ) const {
	return 0;
}

void RockEnemyBossFire::dropItem( ) {
	RockStoragePtr storage( RockStorage::getTask( ) );
	RockFamilyPtr family( RockFamily::getTask( ) );
	int num = 0;
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		if ( family->getPlayer( i )->isActive( ) ) {
			num++;
		}
	}
	for ( int i = 0; i < num; i++ ) {
		storage->addDropItem( RockItemPtr( new RockItemFire( getPos( ) + Vector( i * 20, getRadius( ), 0 ) ) ) );
		storage->addDropItem( RockItemPtr( new RockItemBubble( getPos( ) + Vector( i * 20, getRadius( ), 0 ) ) ) );
	}
}

