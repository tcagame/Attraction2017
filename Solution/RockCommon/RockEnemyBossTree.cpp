#include "RockEnemyBossTree.h"
#include "RockStorage.h"
#include "RockitemTree.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockDollHouse.h"

const int HP = 10;
static const double ANIM_SPEED = 0.9;


RockEnemyBossTree::RockEnemyBossTree( const Vector& pos ) :
RockEnemyBoss( pos, DOLL_BOSS_TREE, HP, 1, 10, 10, true, true ) {
	setDir( Vector( -1, 0, 0 ) );
}


RockEnemyBossTree::~RockEnemyBossTree( ) {
}

void RockEnemyBossTree::act( ) {

}

double RockEnemyBossTree::getAnimTime( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	double anim_time = 0;
	double end_time = model->getEndAnimTime( );	
	anim_time = fmod( ( double )getActCount( ) * ANIM_SPEED, end_time );
	return anim_time;
}

void RockEnemyBossTree::dropItem( ) {
	RockStoragePtr storage( RockStorage::getTask( ) );
	
	storage->addDropItem( RockItemPtr( new RockItemTree( getPos( ) + Vector( 20, getOverlappedRadius( ), 0 ) ) ) );
}
