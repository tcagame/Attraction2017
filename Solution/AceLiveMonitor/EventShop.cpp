#include "EventShop.h"
#include "Office.h"
#include "Storage.h"
#include "Family.h"
#include "Player.h"
#include "ItemDango.h"
#include "ItemEnhancedAttack.h"
#include "ItemEnhancedCharge.h"
#include "ItemYokaiSoup.h"

const int START_POS_X = 256 + ( 1280 / 2 - 256 ) / 2;
const int START_POS_Y = 128;

EventShop::EventShop( ) :
Event( EVENT_SHOP, DIR_LEFT ) {
	Office::getTask( )->popUpNPC( EVENT_SHOP );
	// ここにショップのアイテムを設定
	StoragePtr storage = Storage::getTask( );
	storage->add( ShopItemPtr( new ItemDango( Vector( 450, 0 ) ) ) );
 	storage->add( ShopItemPtr( new ItemEnhancedAttack( Vector( 530, 0 ) ) ) );
	storage->add( ShopItemPtr( new ItemEnhancedCharge( Vector( 610, 0 ) ) ) );
	storage->add( ShopItemPtr( new ItemYokaiSoup( Vector( 690, 0 ) ) ) );
}


EventShop::~EventShop( ) {
}

void EventShop::update( ) {
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		PlayerPtr player = Family::getTask( )->getPlayer( i );
		if ( player->isEntering( ) ) {
			player->enterEvent( START_POS_X, START_POS_Y ); // 本来は出現位置や自動移動などを設定する
		}
	}
}

bool EventShop::isJoining( ) const {
	//return false;
	return getFade( ) != FADE_OUT;
}

void EventShop::join( PLAYER target ) {
	PlayerPtr player = Family::getTask( )->getPlayer( target );
	player->setActionEnteringFadeOut( );
	start( );
}