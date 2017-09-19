#include "RockEnemyBossRedDaemon.h"
#include "RockStorage.h"
#include "RockItemFire.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockDollHouse.h"

const int HP = 1;
static const double ANIM_SPEED = 0.9;

RockEnemyBossRedDaemon::RockEnemyBossRedDaemon( const Vector& pos ) :
RockEnemyBoss( pos, DOLL_BOSS_RED_DAEMON, HP, 1, 10, 10, true, true ) {
}


RockEnemyBossRedDaemon::~RockEnemyBossRedDaemon( ) {
}

void RockEnemyBossRedDaemon::act( ) {
	return;
}

double RockEnemyBossRedDaemon::getAnimTime( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	double anim_time = 0;
	double end_time = model->getEndAnimTime( );	
	anim_time = fmod( ( double )getActCount( ) * ANIM_SPEED, end_time );
	return anim_time;
}