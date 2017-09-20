#include "RockEnemyLittleRedDaemon.h"
#include "RockStorage.h"
#include "RockItemMoney.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockDollHouse.h"

const int HP = 3;
const double ACCEL = 0.1;
const double MAX_SPEED = 1.5;
const double ANIM_SPEED = 0.9;
const Vector SEARCH_RANGE( 500, 500, 500 );

RockEnemyLittleRedDaemon::RockEnemyLittleRedDaemon( const Vector& pos ) :
RockEnemyBoss( pos, DOLL_LITTLE_RED_DAMON, HP, 1, 15, 10, true, true ),
_player_radius( 0 ) {
}


RockEnemyLittleRedDaemon::~RockEnemyLittleRedDaemon( ) {
}

void RockEnemyLittleRedDaemon::act( ) {
	Vector near_distance = SEARCH_RANGE;
	bool wait = true;
	for (int i = 0; i < ROCK_PLAYER_NUM; i++) {
		RockPlayerPtr player = RockFamily::getTask( )->getPlayer( i );
		if ( !player->isActive( ) || player->isBubble( ) ) {
			continue;
		}
		wait = false;
		Vector distance = player->getPos( ) - getPos( );
		if ( near_distance.getLength( ) > distance.getLength( ) ) {
			near_distance = distance;
		}
	}
	if ( near_distance != SEARCH_RANGE ) {
		Vector dir = near_distance.normalize( );
		Vector vec = getVec( ) + dir * ACCEL;
		if ( vec.getLength2( ) > MAX_SPEED * MAX_SPEED ) {
			vec = vec.normalize( ) * MAX_SPEED;
		}
		setVec( vec );
	}
	if ( wait ) {
		setVec( Vector( ) );
	}
}

double RockEnemyLittleRedDaemon::getAnimTime( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	double anim_time = 0;
	double end_time = model->getEndAnimTime( );	
	anim_time = fmod( ( double )getActCount( ) * ANIM_SPEED, end_time );
	return anim_time;
}
