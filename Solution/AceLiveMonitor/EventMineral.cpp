#include "EventMineral.h"
#include "Military.h"
#include "EnemyBossRock.h"
#include "Family.h"
#include "Player.h"

EventMineral::EventMineral( ) :
Event( EVENT_MINERAL ) {
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
			player->enterEvent( );
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
	player->setActionEnteringFadeOut( );
}