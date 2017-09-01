#include "RockEnemyFaceAndHand.h"
#include "RockStorage.h"
#include "RockItemMoney.h"
#include "RockFamily.h"
#include "RockPlayer.h"

const int HP = 20;
const int MOVE_SPEED = 1;
const Vector SEARCH_RANGE( 10000, 10000, 10000 );

RockEnemyFaceAndHand::RockEnemyFaceAndHand( const Vector& pos ) :
RockEnemy( pos, DOLL_FACE_AND_HAND, HP, 1, 10, 10, false, true ),
_player_radius( 0 ) {
}


RockEnemyFaceAndHand::~RockEnemyFaceAndHand( ) {
}

void RockEnemyFaceAndHand::act( ) {
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

double RockEnemyFaceAndHand::getAnimTime( ) const {
	return 0;
}

void RockEnemyFaceAndHand::dropItem( ) {
	RockStorage::getTask( )->addDropItem( RockItemPtr( new RockItemMoney( getPos( ) + Vector( 0, getRadius( ), 0 ), RockItemMoney::MONEY_VALUE_3 ) ) );
}