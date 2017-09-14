#include "EventShop.h"
#include "Office.h"
#include "Storage.h"

EventShop::EventShop( ) :
Event( EVENT_SHOP ) {
	Office::getTask( )->popUpNPC( EVENT_SHOP );
	Storage::getTask( )->createShopItem( );
}


EventShop::~EventShop( ) {
}

void EventShop::update( ) {
}

