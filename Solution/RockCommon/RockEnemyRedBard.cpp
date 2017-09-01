#include "RockEnemyRedBard.h"
#include "RockStorage.h"
#include "RockItemMoney.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockDollHouse.h"

const int HP = 20;
const int MOVE_SPEED = 1;
static const double ANIM_SPEED = 0.9;
const Vector SEARCH_RANGE( 10000, 10000, 10000 );

RockEnemyRedBard::RockEnemyRedBard( const Vector& pos ) :
RockEnemy( pos, DOLL_REDBARD, HP, 1, 10, 10, false, true ),
_player_radius( 0 ) {
}


RockEnemyRedBard::~RockEnemyRedBard( ) {
}

void RockEnemyRedBard::act( ) {
	Vector near_distance = SEARCH_RANGE;
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		RockPlayerPtr player = RockFamily::getTask( )->getPlayer( i );
		_player_radius = player->getRadius( );
		if ( !player->isActive( ) || player->isBubble( ) ) {
			setVec( Vector( ) );
			continue;
		}
		Vector distance = player->getPos( ) - getPos( );
		if ( near_distance.getLength( ) > distance.getLength( ) ) {
			near_distance = distance;
		}
	}
	if ( near_distance != SEARCH_RANGE ) {
		Vector dir = near_distance.normalize( );	
		Vector vec = dir * MOVE_SPEED;
		setVec( vec );
		if ( near_distance.getLength( ) < MOVE_SPEED + ( getRadius( ) + _player_radius ) - 1 ) {
			setVec( Vector( ) );
		}
	}
}

double RockEnemyRedBard::getAnimTime( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	double anim_time = 0;
	double end_time = model->getEndAnimTime( );	
	anim_time = fmod( ( double )getActCount( ) * ANIM_SPEED, end_time );
	return anim_time;
}

void RockEnemyRedBard::dropItem( ) {
	RockStorage::getTask( )->addDropItem( RockItemPtr( new RockItemMoney( getPos( ) + Vector( 0, getRadius( ), 0 ), RockItemMoney::MONEY_VALUE_3 ) ) );
}