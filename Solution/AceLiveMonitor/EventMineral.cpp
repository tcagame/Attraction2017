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

bool EventMineral::isJoining( ) const {
	return getFade( ) != FADE_OUT;
}

void EventMineral::join( PLAYER target ) {
	PlayerPtr player = Family::getTask( )->getPlayer( target );
	if ( !player->isWearingItem( Player::ITEM_MINERAL ) ) {
		player->setActionEnteringFadeOut( );
		start( );
	}
}