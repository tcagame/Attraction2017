#include "EventShop.h"
#include "Office.h"
#include "Storage.h"
#include "Family.h"
#include "Player.h"
#include "ItemDango.h"
#include "ItemEnhancedAttack.h"
#include "ItemEnhancedCharge.h"
#include "ItemYokaiSoup.h"

const int START_POS_X = 310;
const int START_POS_Y = 128;

EventShop::EventShop( ) :
Event( EVENT_SHOP, DIR_LEFT ) {
	Office::getTask( )->popUpNPC( EVENT_SHOP );
	// ここにショップのアイテムを設定
	StoragePtr storage = Storage::getTask( );
	storage->add( ShopItemPtr( new ItemDango( Vector( 450, 150 ) ) ) );
 	storage->add( ShopItemPtr( new ItemEnhancedAttack( Vector( 530, 150 ) ) ) );
	storage->add( ShopItemPtr( new ItemEnhancedCharge( Vector( 610, 150 ) ) ) );
	storage->add( ShopItemPtr( new ItemYokaiSoup( Vector( 690, 150 ) ) ) );
}


EventShop::~EventShop( ) {
}

void EventShop::update( ) {
	escape( );
}

void EventShop::join( PLAYER target ) {
	if ( getFade( ) == FADE_OUT ) {
		return;
	}
	PlayerPtr player = Family::getTask( )->getPlayer( target );
	player->enterEvent( Vector( START_POS_X, START_POS_Y ), Player::ENTER_FADEOUT );
}