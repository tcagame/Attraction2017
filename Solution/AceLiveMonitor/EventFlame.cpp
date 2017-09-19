#include "EventFlame.h"
#include "Military.h"
#include "EnemyBossBloodDaemon.h"
#include "Family.h"
#include "Player.h"

EventFlame::EventFlame( ) :
Event( EVENT_FLAME ) {
	_boss = EnemyBossPtr( new EnemyBossBloodDaemon( Vector( 800, 200 ) ) );
	Military::getTask( )->popUp( _boss );
}


EventFlame::~EventFlame( ) {
}

void EventFlame::update( ) {
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

bool EventFlame::isJoining( ) const {
	return getFade( ) != FADE_OUT;
}

void EventFlame::join( PLAYER target ) {
	PlayerPtr player = Family::getTask( )->getPlayer( target );
	player->setActionEnteringFadeOut( );
}