#include "RockMapBoss.h"
#include "RockMapBossDrawer.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockMilitary.h"
#include "RockStorage.h"
#include "Status.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "MessageSender.h"
#include "RockEnemyBossRock.h"
#include "RockEnemyBossFire.h"
#include "RockEnemyBossTree.h"
#include "RockArmoury.h"
#include "RockShot.h"
#include "Sound.h"

const int WARP_RANGE = 75;

RockMapBoss::RockMapBoss( StatusPtr status ) :
_status( status ) {
}

RockMapBoss::~RockMapBoss( ) {
}

void RockMapBoss::initialize( ) {
	_drawer = RockMapBossDrawerPtr( new RockMapBossDrawer( STAGE_ROCK ) );
	Sound::getTask( )->stopBGM( );
}

void RockMapBoss::update( ) {
	RockFamilyPtr family( RockFamily::getTask( ) );
	bool reset_stage = true;
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		if ( !family->getPlayer( i )->isActive( ) ) {
			continue;
		}
		reset_stage = false;
	}

	if ( reset_stage ) {
		Sound::getTask( )->stopBGM( );
		RockArmoury::getTask( )->clearShot( );
		RockMilitary::getTask( )->clean( );
		RockStorage::getTask( )->clean( );
	}

	STAGE now = _drawer->getStage( );
	if ( reset_stage &&
		 now != STAGE_TREE_TO_FIRE ) {
		_drawer.reset( );
		_drawer = RockMapBossDrawerPtr( new RockMapBossDrawer( STAGE_TREE_TO_FIRE ) );
		return;
	}

	//一定の位置に行くとマップ切り替え
	RockMilitaryPtr military( RockMilitary::getTask( ) );
	SoundPtr sound = Sound::getTask( );
	switch ( now ) {
	case STAGE_TREE_TO_FIRE:
		if ( isWarpToBoss( Vector( 1550, 0, -50 ) ) ) {
			sound->playBGM( "yokai_music_04.wav" );
			RockFamily::getTask( )->resetPos( Vector( 0, 0, 0 ) ); // room_fire
			military->clean( );
			military->addEnemy( RockEnemyPtr( new RockEnemyBossFire( Vector( 220, 10, -20 ) ) ) );
			break;
		}
		return;
	case STAGE_FIRE:
		if ( isWarpToStreet( STAGE_FIRE ) ) {
			sound->stopBGM( );
			RockFamily::getTask( )->resetPos( Vector( -700, 75, -25 ) ); // fire to rock
			military->clean( );
			break;
		}
		return;
	case STAGE_FIRE_TO_ROCK:
		if ( isWarpToBoss( Vector( 1550, 0, -50 ) ) ) {
			sound->playBGM( "yokai_music_04.wav" );
			//STAGE_ROCKへ行く
			RockFamily::getTask( )->resetPos( Vector( 0, 0, 0 ) );
			military->clean( );
			military->addEnemy( RockEnemyPtr( new RockEnemyBossRock( Vector( 300, 10, 0 ) ) ) );
			break;
		}
		return;
	case STAGE_ROCK:
		if ( isWarpToStreet( STAGE_ROCK ) ) {
			sound->stopBGM( );
			RockFamily::getTask( )->resetPos( Vector( -700, 75, -25 ) ); // rock to tree
			military->clean( );
			break;
		}
		return;
	case STAGE_ROCK_TO_TREE:
		if ( isWarpToBoss( Vector( 1550, 0, -50 ) ) ) {
			sound->playBGM( "yokai_music_04.wav" );
			RockFamily::getTask( )->resetPos( Vector( 0, 0, 0 ) ); // tree
			military->clean( );
			military->addEnemy( RockEnemyPtr( new RockEnemyBossTree( Vector( 300, 10, 0 ) ) ) );
			break;
		}
		return;
	case STAGE_TREE:
		if ( isWarpToStreet( STAGE_TREE ) ) {
			sound->stopBGM( );
			RockFamily::getTask( )->resetPos( Vector( -700, 75, -25 ) ); // tree to fire
			military->clean( );
			break;
		}
		return;
	}
	RockStorage::getTask( )->clean( );
	STAGE next = ( STAGE )( ( now + 1 ) % ( int )MAX_STAGE );
	_drawer.reset( );
	_drawer = RockMapBossDrawerPtr( new RockMapBossDrawer( next ) );
}

bool RockMapBoss::isWarpToBoss( const Vector& pos ) {
	RockFamilyPtr family( RockFamily::getTask( ) );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		RockPlayerPtr player( family->getPlayer( i ) );
		if ( !player->isActive( ) ) {
			Sound::getTask( )->stopBGM( );
			continue;
		}
		Vector p_pos = player->getPos( );
		Vector diff = p_pos - pos;
		double radius = player->getOverlappedRadius( );
		if ( diff.getLength2( ) < WARP_RANGE * WARP_RANGE ) {
			return true;
		}
	}
	return false;
}

bool RockMapBoss::isWarpToStreet( STAGE stage ) {
	unsigned char sacred = 0;
	switch ( stage ) {
	case STAGE_FIRE:
		sacred = ITEM_FIRE;
		break;
	case STAGE_ROCK:
		sacred = ITEM_ROCK;
		break;
	case STAGE_TREE:
		sacred = ITEM_TREE;
		break;
	default:
		return false;
		break;
	}

	RockFamilyPtr family( RockFamily::getTask( ) );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		RockPlayerPtr player( family->getPlayer( i ) );
		if ( !player->isActive( ) ) {
		Sound::getTask( )->stopBGM( );
			continue;
		}
		if ( !( _status->getPlayer( i ).item & sacred ) ) {
			return false;
		}
	}
	return true;
}

RockMapBoss::STAGE RockMapBoss::getStage( ) const {
	return _drawer->getStage( );
}

