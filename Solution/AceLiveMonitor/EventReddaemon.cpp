#include "EventReddaemon.h"
#include "Military.h"
#include "EnemyBossRedDaemon.h"
#include "Family.h"
#include "Player.h"

EventReddaemon::EventReddaemon( ) :
Event( EVENT_REDDAEMON, DIR_LEFT ) {
	_boss = EnemyBossPtr( new EnemyBossRedDaemon( Vector( 800, 200 ) ) );
	Military::getTask( )->popUp( _boss );
}


EventReddaemon::~EventReddaemon( ) {
}

void EventReddaemon::update( ) {
	// 透明化し切ったら、イベントへ
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		PlayerPtr player = Family::getTask( )->getPlayer( i );
		if ( player->isEntering( ) ) {
			player->enterEvent( );
		}
	}

	// ボスを倒した
	if ( _boss->getPower( ) <= 0 ) {
		exit( );
	}
}

bool EventReddaemon::isJoining( ) const {
	return getFade( ) != FADE_OUT;
}

void EventReddaemon::join( PLAYER target ) {
	PlayerPtr player = Family::getTask( )->getPlayer( target );
	player->setActionEnteringFadeOut( );
	start( );
}