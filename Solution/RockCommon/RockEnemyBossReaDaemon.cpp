#include "RockEnemyBossReaDaemon.h"
#include "RockStorage.h"
#include "RockItemFire.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockDollHouse.h"

const int HP = 10;
static const double ANIM_SPEED = 0.9;

RockEnemyBossReaDaemon::RockEnemyBossReaDaemon( const Vector& pos ) :
RockEnemyBoss( pos, DOLL_BOSS_RED_DAEMON, HP, 1, 10, 10, true, true ) {
}


RockEnemyBossReaDaemon::~RockEnemyBossReaDaemon( ) {
}

void RockEnemyBossReaDaemon::act( ) {
	return;
}

double RockEnemyBossReaDaemon::getAnimTime( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	double anim_time = 0;
	double end_time = model->getEndAnimTime( );	
	anim_time = fmod( ( double )getActCount( ) * ANIM_SPEED, end_time );
	return anim_time;
}
