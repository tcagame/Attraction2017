#include "RockEnemyGhost.h"
#include "RockStorage.h"
#include "RockItemMoney.h"
#include "RockPlayer.h"
#include "RockFamily.h"
#include "RockDollHouse.h"

const int HP = 10;
const double ACCEL = 0.1;
const double MAX_SPEED = 2.2;
const double ANIM_SPEED = 0.9;
const Vector SEARCH_RANGE( 1000, 1000, 1000 );

RockEnemyGhost::RockEnemyGhost( const Vector& pos ) :
RockEnemy( pos, DOLL_GHOST, HP, 1, 10, 10, false, false ),
_player_radius( 0 ) {
}


RockEnemyGhost::~RockEnemyGhost( ) {
}

void RockEnemyGhost::act( ) {
	Vector near_distance = SEARCH_RANGE;
	bool wait = true;
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
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

double RockEnemyGhost::getAnimTime( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	double anim_time = 0;
	double end_time = model->getEndAnimTime( );	
	anim_time = fmod( ( double )getActCount( ) * ANIM_SPEED, end_time );
	return anim_time;
}

void RockEnemyGhost::dropItem( ) {
	RockStorage::getTask( )->addDropItem( RockItemPtr( new RockItemMoney( getPos( ) + Vector( 0, getOverlappedRadius( ), 0 ), RockItemMoney::MONEY_VALUE_2 ) ) );
}
