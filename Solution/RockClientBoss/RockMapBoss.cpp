#include "RockMapBoss.h"
#include "RockMapBossDrawer.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockMilitatyBoss.h"
#include "RockEnemyBossRock.h"
#include "RockStorage.h"
#include "Status.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "MessageSender.h"

const int WARP_RANGE = 75;

RockMapBoss::RockMapBoss( StatusPtr status ) :
_status( status ) {
}

RockMapBoss::~RockMapBoss( ) {
}

void RockMapBoss::initialize( ) {
	_drawer = RockMapBossDrawerPtr( new RockMapBossDrawer( STAGE_TREE_TO_FIRE ) );
}

void RockMapBoss::update( ) {
	RockFamilyPtr family( RockFamily::getTask( ) );
	bool reset_stage[ ROCK_PLAYER_NUM ] = { false };
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		if ( !family->getPlayer( i )->isActive( ) ) {
			reset_stage[ i ] = true;
			continue;
		}
		Status::Player player = _status->getPlayer( i );
		unsigned char item = player.item;
		//神器を持っていると、STREET_3へ移動
		if ( ( item & ITEM_FIRE ) &&
			 ( item & ITEM_ROCK ) &&
			 ( item & ITEM_TREE ) ) {
			unsigned char state = AREA_STREET_3;
			MessageSender::getTask( )->sendMessage( i, Message::COMMAND_STATE, &state );
		}
	}

	STAGE now = _drawer->getStage( );
	if ( reset_stage[ 0 ] &&
		 reset_stage[ 1 ] &&
		 reset_stage[ 2 ] &&
		 reset_stage[ 3 ] &&
		 now != STAGE_TREE_TO_FIRE ) {
		_drawer.reset( );
		_drawer = RockMapBossDrawerPtr( new RockMapBossDrawer( STAGE_TREE_TO_FIRE ) );
		return;
	}

	//一定の位置に行くとマップ切り替え
	switch ( now ) {
	case STAGE_TREE_TO_FIRE:
		if ( isWarp( Vector( 1550, 0, -50 ) ) ) {
			RockFamily::getTask( )->resetPos( Vector( 0, 0, 0 ) ); // room_fire
			break;
		}
		return;
	case STAGE_FIRE:
		if ( isWarp( Vector( 240, 0, -25 ) ) ) {
			RockFamily::getTask( )->resetPos( Vector( -700, 75, -25 ) ); // fire to rock
			break;
		}
		return;
	case STAGE_FIRE_TO_ROCK:
		if ( isWarp( Vector( 1550, 0, -50 ) ) ) {
			//STAGE_ROCKへ行く
			RockFamily::getTask( )->resetPos( Vector( 0, 0, 0 ) );
			RockMilitatyBoss::getTask( )->add( RockEnemyPtr( new RockEnemyBossRock( Vector( 300, 10, 0 ) ) ) );
			break;
		}
		return;
	case STAGE_ROCK:
		if ( isWarp( Vector( 600, 0, 0 ) ) ) {
			RockFamily::getTask( )->resetPos( Vector( -700, 75, -25 ) ); // rock to tree
			break;
		}
		return;
	case STAGE_ROCK_TO_TREE:
		if ( isWarp( Vector( 1550, 0, -50 ) ) ) {
			RockFamily::getTask( )->resetPos( Vector( 0, 0, 0 ) ); // tree
			break;
		}
		return;
	case STAGE_TREE:
		if ( isWarp( Vector( 600, 0, 0 ) ) ) {
			RockFamily::getTask( )->resetPos( Vector( -700, 75, -25 ) ); // tree to fire
			break;
		}
		return;
	}
	RockStorage::getTask( )->clean( );
	STAGE next = ( STAGE )( ( now + 1 ) % ( int )MAX_STAGE );
	_drawer.reset( );
	_drawer = RockMapBossDrawerPtr( new RockMapBossDrawer( next ) );
}

bool RockMapBoss::isWarp( const Vector& pos ) {
	RockFamilyPtr family( RockFamily::getTask( ) );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		RockPlayerPtr player( family->getPlayer( i ) );
		Vector p_pos = player->getPos( );
		Vector diff = p_pos - pos;
		double radius = player->getRadius( );
		if ( diff.getLength2( ) < WARP_RANGE * WARP_RANGE ) {
			return true;
		}
	}
	return false;
}
