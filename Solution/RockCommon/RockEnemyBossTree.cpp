#include "RockEnemyBossTree.h"
#include "RockStorage.h"
#include "RockitemTree.h"
#include "RockItemBubble.h"
#include "RockFamily.h"
#include "RockPlayer.h"

const int HP = 10;

RockEnemyBossTree::RockEnemyBossTree( const Vector& pos ) :
RockEnemyBoss( pos, DOLL_GHOST, HP, 1, 10, 10, true, true ) {
}


RockEnemyBossTree::~RockEnemyBossTree( ) {
}

void RockEnemyBossTree::act( ) {

}

double RockEnemyBossTree::getAnimTime( ) const {
	return 0;
}

void RockEnemyBossTree::dropItem( ) {
	RockStoragePtr storage( RockStorage::getTask( ) );
	RockFamilyPtr family( RockFamily::getTask( ) );
	int num = 0;
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		if ( family->getPlayer( i )->isActive( ) ) {
			num++;
		}
	}
	for ( int i = 0; i < num; i++ ) {
		storage->addDropItem( RockItemPtr( new RockItemTree( getPos( ) + Vector( i * 20, getRadius( ), 0 ) ) ) );
		storage->addDropItem( RockItemPtr( new RockItemBubble( getPos( ) + Vector( i * 20, getRadius( ), 0 ) ) ) );
	}
}
