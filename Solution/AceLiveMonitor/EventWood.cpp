#include "EventWood.h"
#include "Military.h"
#include "EnemyBossMonsterTree.h"
#include "Family.h"
#include "Player.h"

const int START_POS_X = 256 + ( 1280 / 2 - 256 ) / 2;
const int START_POS_Y = 128;

EventWood::EventWood( ) :
Event( EVENT_WOOD, DIR_LEFT ) {
	_boss = EnemyBossPtr( new EnemyBossMonsterTree( Vector( 800, 225 ) ) );
	Military::getTask( )->popUp( _boss );
}


EventWood::~EventWood( ) {
}

void EventWood::update( ) {
	// ボスを倒した
	if ( _boss->getPower( ) <= 0 ) {
		_boss->dropItem( );//神器(木)を配る
		exit( );
	}
	escape( );
}

void EventWood::join( PLAYER target ) {
	if ( getFade( ) == FADE_OUT ) {
		return;
	}
	PlayerPtr player = Family::getTask( )->getPlayer( target );
	if ( !player->isWearingItem( Player::ITEM_WOOD ) ) {
		player->enterEvent( Vector( START_POS_X, START_POS_Y ), Player::ENTER_SANZO );
		start( );
	}
}