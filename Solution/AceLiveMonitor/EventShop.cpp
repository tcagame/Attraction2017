#include "EventShop.h"
#include "Office.h"
#include "Storage.h"
#include "Family.h"
#include "Player.h"

const int START_POS_X = 256 + ( 1280 / 2 - 256 ) / 2;
const int START_POS_Y = 128;

EventShop::EventShop( ) :
Event( EVENT_SHOP, DIR_LEFT ) {
	Office::getTask( )->popUpNPC( EVENT_SHOP );
	// �����ɃV���b�v�̃A�C�e����ݒ�
}


EventShop::~EventShop( ) {
}

void EventShop::update( ) {
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		PlayerPtr player = Family::getTask( )->getPlayer( i );
		if ( player->isEntering( ) ) {
			player->enterEvent( START_POS_X, START_POS_Y ); // �{���͏o���ʒu�⎩���ړ��Ȃǂ�ݒ肷��
		}
	}
}

bool EventShop::isFinished( ) const {
	return false;
}

bool EventShop::isJoining( ) const {
	return getFade( ) != FADE_OUT;
}

void EventShop::join( PLAYER target ) {
	PlayerPtr player = Family::getTask( )->getPlayer( target );
	player->setActionEnteringSanzo( );
	start( );
}