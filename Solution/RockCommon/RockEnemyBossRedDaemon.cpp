#include "RockEnemyBossRedDaemon.h"
#include "RockStorage.h"
#include "RockItemFire.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockDollHouse.h"
#include "RockMilitary.h"
#include "RockEnemyLittleRedDaemon.h"

const int HP = 10;
const double ANIM_SPEED = 0.9;
const int GENERATE_NUM = 4;
const int GENERATE_TIME = 300;
const int POP_NUM = 4;

RockEnemyBossRedDaemon::RockEnemyBossRedDaemon( const Vector& pos ) :
RockEnemyBoss( pos, DOLL_BOSS_RED_DAEMON, HP, 1, 30, 10, true, true ),
_count( 0 ) {
}


RockEnemyBossRedDaemon::~RockEnemyBossRedDaemon( ) {
}

void RockEnemyBossRedDaemon::act( ) {
	Vector generate_pos( getPos( ) );
	const Vector GENERATE_POS[ GENERATE_NUM ] = { 
		Vector( generate_pos.x + 30, generate_pos.y, generate_pos.z ),
		Vector( generate_pos.x - 30, generate_pos.y, generate_pos.z ),
		Vector( generate_pos.x, generate_pos.y, generate_pos.z + 30 ),
		Vector( generate_pos.x, generate_pos.y, generate_pos.z - 30 ),
	};

	RockMilitaryPtr military = RockMilitary::getTask( );
	if ( getActCount( ) % GENERATE_TIME == 0 && _count < POP_NUM ) {
		for ( int i = 0; i < GENERATE_NUM; i++ ) {
			military->addEnemy( RockEnemyPtr( new RockEnemyLittleRedDaemon( GENERATE_POS[ i ] ) ) );
		}
		_count++;
	}
}

double RockEnemyBossRedDaemon::getAnimTime( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	double anim_time = 0;
	double end_time = model->getEndAnimTime( );	
	anim_time = fmod( ( double )getActCount( ) * ANIM_SPEED, end_time );
	return anim_time;
}
