#include "EventReddaemon.h"
#include "Military.h"
#include "EnemyBossRedDaemon.h"
#include "Family.h"
#include "Player.h"

EventReddaemon::EventReddaemon( ) :
Event( EVENT_REDDAEMON ) {
	_boss = EnemyBossPtr( new EnemyBossRedDaemon( Vector( 800, 200 ) ) );
	Military::getTask( )->popUp( _boss );
}


EventReddaemon::~EventReddaemon( ) {
}

void EventReddaemon::update( ) {
	if ( _boss->getPower( ) <= 0 ) {
		exit( );
	}
}

bool EventReddaemon::isJoining( ) const {
	return true;
}

void EventReddaemon::join( PLAYER target ) {
	PlayerPtr player = Family::getTask( )->getPlayer( target );
	player->enterEvent( );
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