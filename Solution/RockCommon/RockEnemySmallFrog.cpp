#include "RockEnemySmallFrog.h"
#include "RockStorage.h"
#include "RockItemMoney.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockDollHouse.h"

const int HP = 2;
const double ACCEL = 0.1;
const double MAX_SPEED = 1.5;
const double ANIM_SPEED = 0.9;
const Vector SEARCH_RANGE( 1000, 1000, 1000 );

RockEnemySmallFrog::RockEnemySmallFrog( const Vector& pos ) :
RockEnemy( pos, DOLL_FLOG_1, HP, 1, 10, 10, true, true ),
_player_radius( 0 ) {
	setVec( Vector( 0, -5, 0 ) );
}


RockEnemySmallFrog::~RockEnemySmallFrog( ) {
}

void RockEnemySmallFrog::act( ) {
	Vector near_distance = SEARCH_RANGE;
	bool wait = true;
	for (int i = 0; i < ROCK_PLAYER_NUM; i++) {
		RockPlayerPtr player = RockFamily::getTask( )->getPlayer( i );
		if ( !player->isActive( ) || player->isBubble( ) ) {
			continue;
		}
		if ( isOnHead( player ) ) {
			damage( -1 );
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
		vec.y = getVec( ).y;
		setVec( vec );
	}
	if ( wait ) {
		setVec( Vector( ) );
	}
}

double RockEnemySmallFrog::getAnimTime( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	double anim_time = 0;
	double end_time = model->getEndAnimTime( );	
	anim_time = fmod( ( double )getActCount( ) * ANIM_SPEED, end_time );
	return anim_time;
}

void RockEnemySmallFrog::dropItem( ) {
	RockStorage::getTask( )->addDropItem( RockItemPtr( new RockItemMoney( getPos( ) + Vector( 0, getOverlappedRadius( ), 0 ), RockItemMoney::MONEY_VALUE_3 ) ) );
}