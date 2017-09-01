#include "RockEnemyBossFire.h"
#include "RockStorage.h"
#include "RockItemFire.h"
#include "RockItemBubble.h"

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
	storage->addDropItem( RockItemPtr( new RockItemFire( getPos( ) + Vector( 0, getRadius( ), 0 ) ) ) );
	storage->addDropItem( RockItemPtr( new RockItemBubble( getPos( ) + Vector( 0, getRadius( ), 0 ) ) ) );
}

