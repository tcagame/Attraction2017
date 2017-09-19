#include "EventFlame.h"
#include "Military.h"
#include "EnemyBossBloodDaemon.h"
#include "Family.h"
#include "Player.h"

const int START_POS_X = 256 + ( 1280 / 2 - 256 ) / 2;
const int START_POS_Y = 128;

EventFlame::EventFlame( ) :
Event( EVENT_FLAME, DIR_LEFT ) {
	_boss = EnemyBossPtr( new EnemyBossBloodDaemon( Vector( 800, 200 ) ) );
	Military::getTask( )->popUp( _boss );
}


EventFlame::~EventFlame( ) {
}

void EventFlame::update( ) {
	// 透明化し切ったら、イベントへ
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		PlayerPtr player = Family::getTask( )->getPlayer( i );
		if ( player->isEntering( ) ) {
			player->enterEvent( START_POS_X, START_POS_Y );
		}
	}

	// ボスを倒した
	if ( _boss->getPower( ) <= 0 ) {
		_boss->dropItem( );//神器(火)を配る
		exit( );
	}
}

bool EventFlame::isJoining( ) const {
	return getFade( ) != FADE_OUT;
}

void EventFlame::join( PLAYER target ) {
	PlayerPtr player = Family::getTask( )->getPlayer( target );
	if ( !player->isWearingItem( Player::ITEM_FLAME ) ) {
		player->setActionEnteringFadeOut( );
		start( );
	}
}

int EventFlame::getLeavePosX( ) const {
	return GRAPH_SIZE;
}
