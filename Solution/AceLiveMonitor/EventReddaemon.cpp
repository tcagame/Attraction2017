#include "EventReddaemon.h"
#include "Military.h"
#include "EnemyBossRedDaemon.h"

EventReddaemon::EventReddaemon( ) :
Event( EVENT_REDDAEMON ) {
	_boss = EnemyBossPtr( new EnemyBossRedDaemon( Vector( 800, 200 ) ) );
	Military::getTask( )->popUp( _boss );
}


EventReddaemon::~EventReddaemon( ) {
}

void EventReddaemon::update( ) {
}


bool EventReddaemon::isFinished( ) const {
	return true;
}

bool EventReddaemon::isJoining( ) const {
	return false;
}

void EventReddaemon::join( PLAYER target ) {

}
/*
void Military::updateBoss( ) {
	if ( !_boss ) {
		return;
	}
	FamilyPtr family( Family::getTask( ) );
	int camera_pos = family->getCameraPosX( );

	_boss->update( );
	_boss->setSynchronousData( SynchronousData::TYPE_ENEMY_BOSS, camera_pos );

	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		PlayerPtr player( family->getPlayer( i ) );
		if ( player->isOverlapped( _boss ) ) {
			if ( player->isOnHead( _boss ) ) {
				player->bound( );
			} else {
				player->damage( _boss->getForce( ) );
			}
		}
	}
	if ( _boss->getPower( ) <= 0 ) {
		_boss->dropItem( );//—Ž‚¿‚é‚Ì‚Å‚Í‚È‚­”z‚ç‚ê‚é

		SoundPtr sound = Sound::getTask( );
		sound->playSE( "yokai_voice_29.wav" );
		int impact_chip_size = _boss->getChipSize( ) * 2;
		Magazine::getTask( )->add( ImpactPtr( new Impact( _boss->getPos( ) + Vector( 0, _boss->getChipSize( ) / 2 ), AREA_EVENT, impact_chip_size ) ) );
		_boss = EnemyBossPtr( );
	}
}
*/
/*
void Military::createEventEnemy( EVENT type ) {
	switch ( type ) {
	case EVENT_REDDAEMON:
		_enemies.push = EnemyBossPtr( new EnemyBossRedDaemon( Vector( 800, 200 ) ) );
		break;
	case EVENT_FLAME:
		_boss = EnemyBossPtr( new EnemyBossBloodDaemon( Vector( 800, 200 ) ) );
		break;
	case EVENT_WOOD:
		_boss = EnemyBossPtr( new EnemyBossMonsterTree( Vector( 800, 225 ) ) );
		break;
	case EVENT_MINERAL:
		_boss = EnemyBossPtr( new EnemyBossRock( Vector( 800, 225 ) ) );
		break;
	default:
		_boss = EnemyBossPtr( );
		break;
	}
}
*/