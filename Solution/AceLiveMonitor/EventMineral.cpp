#include "EventMineral.h"
#include "Military.h"
#include "EnemyBossRock.h"
#include "Family.h"
#include "Player.h"

const int START_POS_X = 256 + ( 1280 / 2 - 256 ) / 2;
const int START_POS_Y = 128;

EventMineral::EventMineral( ) :
Event( EVENT_MINERAL, DIR_LEFT ) {
	_boss = EnemyBossPtr( new EnemyBossRock( Vector( 800, 225 ) ) );
	Military::getTask( )->popUp( _boss );
}


EventMineral::~EventMineral( ) {
}

void EventMineral::update( ) {
	// ボスを倒した
	if ( _boss->getPower( ) <= 0 ) {
		_boss->dropItem( );//神器(岩)を配る
		exit( );
	}
}

void EventMineral::join( PLAYER target ) {
	if ( getFade( ) == FADE_OUT ) {
		return;
	}
	PlayerPtr player = Family::getTask( )->getPlayer( target );
	if ( !player->isWearingItem( Player::ITEM_MINERAL ) ) {
		player->enterEvent( Vector( START_POS_X, START_POS_Y ), Player::ENTER_SANZO );
		start( );
	}
}