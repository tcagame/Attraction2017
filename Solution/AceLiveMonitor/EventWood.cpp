#include "EventWood.h"
#include "Military.h"
#include "EnemyBossMonsterTree.h"
#include "Family.h"
#include "Player.h"

EventWood::EventWood( ) :
Event( EVENT_WOOD ) {
	_boss = EnemyBossPtr( new EnemyBossMonsterTree( Vector( 800, 225 ) ) );
	Military::getTask( )->popUp( _boss );
}


EventWood::~EventWood( ) {
}

void EventWood::update( ) {
	// 透明化し切ったら、イベントへ
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		PlayerPtr player = Family::getTask( )->getPlayer( i );
		if ( player->isEntering( ) ) {
			player->enterEvent( );
		}
	}

	// ボスを倒した
	if ( _boss->getPower( ) <= 0 ) {
		_boss->dropItem( );//神器(木)を配る
		exit( );
	}
}

bool EventWood::isJoining( ) const {
	return getFade( ) != FADE_OUT;
}

void EventWood::join( PLAYER target ) {
	PlayerPtr player = Family::getTask( )->getPlayer( target );
	player->setActionEnteringFadeOut( );
}