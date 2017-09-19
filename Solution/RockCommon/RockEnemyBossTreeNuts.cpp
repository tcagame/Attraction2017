#include "RockEnemyBossTreeNuts.h"
#include "Effect.h"
#include "RockStudio.h"
#include "RockDollHouse.h"
#include "RockPlayer.h"
#include "RockFamily.h"


const int FORCE = 2;
const Vector SEARCH_RANGE( 10000, 10000, 10000 );
const int MOVE_SPEED = 1;
const int MOVE_TIME = 60;

RockEnemyBossTreeNuts::RockEnemyBossTreeNuts( const Vector pos ) :
RockEnemyAttack( pos, DOLL_TREE_NUTS, 2, FORCE, 10, 30, false, false ),
_player_radius( 0 ) {
	setDir( Vector( -1, 0, 0 ) );
}


RockEnemyBossTreeNuts::~RockEnemyBossTreeNuts( ) {

}

void RockEnemyBossTreeNuts::act( ) {
	Vector near_distance = SEARCH_RANGE;

	if ( getActCount( ) > MOVE_TIME ) {
		for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
			RockPlayerPtr player = RockFamily::getTask( )->getPlayer( i );
			_player_radius = player->getOverlappedRadius( );
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
			if ( near_distance.getLength( ) < MOVE_SPEED + ( getOverlappedRadius( ) + _player_radius ) - 1 ) {
				setVec( Vector( ) );
			}
		}
	}
}

ModelMV1Ptr RockEnemyBossTreeNuts::getModel( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	model->setTrans( Matrix::makeTransformTranslation( getPos( ) ) );
	return model;
}

double RockEnemyBossTreeNuts::getAnimTime( ) const {
	return 0;
}