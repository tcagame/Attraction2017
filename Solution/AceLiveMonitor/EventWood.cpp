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
	// ���������؂�����A�C�x���g��
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		PlayerPtr player = Family::getTask( )->getPlayer( i );
		if ( player->isEntering( ) ) {
			player->enterEvent( START_POS_X, START_POS_Y );
		}
	}

	// �{�X��|����
	if ( _boss->getPower( ) <= 0 ) {
		_boss->dropItem( );//�_��(��)��z��
		exit( );
	}
}

bool EventWood::isJoining( ) const {
	return getFade( ) != FADE_OUT;
}

void EventWood::join( PLAYER target ) {
	PlayerPtr player = Family::getTask( )->getPlayer( target );
	if ( !player->isWearingItem( Player::ITEM_WOOD ) ) {
		player->setActionEnteringFadeOut( );
		start( );
	}
}