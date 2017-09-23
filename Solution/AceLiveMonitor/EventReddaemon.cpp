#include "EventReddaemon.h"
#include "Military.h"
#include "EnemyBossRedDaemon.h"
#include "Family.h"
#include "Player.h"

const int START_POS_X = 256 + ( 1280 / 2 - 256 ) / 2;
const int START_POS_Y = 128;

EventReddaemon::EventReddaemon( ) :
Event( EVENT_REDDAEMON, DIR_LEFT ) {
	_boss = EnemyBossPtr( new EnemyBossRedDaemon( Vector( 900, 220 ) ) );
	Military::getTask( )->popUp( _boss );
}


EventReddaemon::~EventReddaemon( ) {
}

void EventReddaemon::update( ) {
	// ƒ{ƒX‚ð“|‚µ‚½
	if ( _boss->getPower( ) <= 0 ) {
		exit( );
	}
	escape( );
}

void EventReddaemon::join( PLAYER target ) {
	if ( getFade( ) == FADE_OUT ) {
		return;
	}
	PlayerPtr player = Family::getTask( )->getPlayer( target );
	player->enterEvent( Vector( START_POS_X, START_POS_Y ), Player::ENTER_FADEOUT );
}