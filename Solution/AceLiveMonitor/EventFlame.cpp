#include "EventFlame.h"
#include "Military.h"
#include "EnemyBossBloodDaemon.h"
#include "Family.h"
#include "Player.h"

const int START_POS_X = 256 + ( 1280 / 2 - 256 ) / 2;
const int START_POS_Y = 128;
const int FINISHED_COUNT = 100;

EventFlame::EventFlame( ) :
Event( EVENT_FLAME, DIR_LEFT ) {
	_boss = EnemyBossPtr( new EnemyBossBloodDaemon( Vector( 1000, 230 ) ) );
	Military::getTask( )->popUp( _boss );
	_count = 0;
}

EventFlame::~EventFlame( ) {
}

void EventFlame::update( ) {
	// ボスを倒した
	if ( _boss->getPower( ) <= 0 ) {
		_boss->dropItem( );//神器(火)を配る
		if ( _count > FINISHED_COUNT ) {
			exit( );
			_count = 0;
		}
		_count++;
	}
	escape( );
}

void EventFlame::join( PLAYER target ) {
	if ( getFade( ) == FADE_OUT ) {
		return;
	}
	PlayerPtr player = Family::getTask( )->getPlayer( target );
	if ( !player->isWearingItem( Player::ITEM_FLAME ) ) {
		player->enterEvent( Vector( START_POS_X, START_POS_Y ), Player::ENTER_SANZO );
	}
}

int EventFlame::getLeavePosX( ) const {
	return GRAPH_SIZE;
}
