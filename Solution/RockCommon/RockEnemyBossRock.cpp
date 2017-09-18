#include "RockEnemyBossRock.h"
#include "RockStorage.h"
#include "RockItemMoney.h"
#include "RockItemRock.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockDollHouse.h"


const int HP = 50;
static const double ANIM_SPEED = 0.9;


RockEnemyBossRock::RockEnemyBossRock( const Vector& pos ) :
RockEnemyBoss( pos, DOLL_BOSS_ROCK, HP, 1, 10, 10, true, true ) {
	setDir( Vector( -1, 0, 0 ) );
}


RockEnemyBossRock::~RockEnemyBossRock( ) {
}

void RockEnemyBossRock::act( ) {

}

double RockEnemyBossRock::getAnimTime( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	double anim_time = 0;
	double end_time = model->getEndAnimTime( );	
	anim_time = fmod( ( double )getActCount( ) * ANIM_SPEED, end_time );
	return anim_time;
}

void RockEnemyBossRock::dropItem( ) {
	RockStoragePtr storage( RockStorage::getTask( ) );
	
	storage->addDropItem( RockItemPtr( new RockItemRock( getPos( ) + Vector( 20, getOverlappedRadius( ), 0 ) ) ) );
}
