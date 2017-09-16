#include "RockEnemyChivil.h"
#include "RockStorage.h"
#include "RockItemMoney.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockDollHouse.h"

const int HP = 20;
const double ACCEL = 0.1;
const double MAX_SPEED = 1.5;
const double ANIM_SPEED = 0.9;
const Vector SEARCH_RANGE( 10000, 10000, 10000 );

RockEnemyChivil::RockEnemyChivil( const Vector& pos ) :
RockEnemy( pos, DOLL_FACE_AND_HAND, HP, 1, 10, 10, false, true ),
_player_radius( 0 ) {
}


RockEnemyChivil::~RockEnemyChivil( ) {
}

void RockEnemyChivil::act( ) {
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

double RockEnemyChivil::getAnimTime( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	double anim_time = 0;
	double end_time = model->getEndAnimTime( );	
	anim_time = fmod( ( double )getActCount( ) * ANIM_SPEED, end_time );
	return anim_time;
}

void RockEnemyChivil::dropItem( ) {
	RockStorage::getTask( )->addDropItem( RockItemPtr( new RockItemMoney( getPos( ) + Vector( 0, getOverlappedRadius( ), 0 ), RockItemMoney::MONEY_VALUE_3 ) ) );
}