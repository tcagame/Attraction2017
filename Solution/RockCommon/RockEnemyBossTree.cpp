#include "RockEnemyBossTree.h"
#include "RockStorage.h"
#include "RockitemTree.h"
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
	
	storage->addDropItem( RockItemPtr( new RockItemTree( getPos( ) + Vector( 20, getRadius( ), 0 ) ) ) );
}
