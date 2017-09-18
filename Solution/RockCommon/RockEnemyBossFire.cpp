#include "RockEnemyBossFire.h"
#include "RockStorage.h"
#include "RockItemFire.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockDollHouse.h"

const int HP = 10;
static const double ANIM_SPEED = 0.9;


RockEnemyBossFire::RockEnemyBossFire( const Vector& pos ) :
RockEnemyBoss( pos, DOLL_BOSS_FIRE, HP, 1, 10, 10, true, true ) {
	setDir( Vector( -1, 0, 0 ) );
}


RockEnemyBossFire::~RockEnemyBossFire( ) {
}

void RockEnemyBossFire::act( ) {
}

double RockEnemyBossFire::getAnimTime( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	double anim_time = 0;
	double end_time = model->getEndAnimTime( );	
	anim_time = fmod( ( double )getActCount( ) * ANIM_SPEED, end_time );
	return anim_time;
}

void RockEnemyBossFire::dropItem( ) {
	RockStoragePtr storage( RockStorage::getTask( ) );
	
	storage->addDropItem( RockItemPtr( new RockItemFire( getPos( ) + Vector( 20, getOverlappedRadius( ), 0 ) ) ) );
}

