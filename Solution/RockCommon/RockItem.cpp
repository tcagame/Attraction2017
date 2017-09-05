#include "RockItem.h"

RockItem::RockItem( const Vector& pos, DOLL doll, int price ) :
RockCharacter( pos, doll, 10, 10 ),
_repop( true ),
_shop_item( false ),
_price( price ) {
}

RockItem::~RockItem( ) {
}

void RockItem::act( ) {
}

void RockItem::setRepop( bool repop ) {
	_repop = repop;
}

void RockItem::setShopItem( bool shop_item ) {
	_shop_item = shop_item;
}

bool RockItem::isRepop( ) const {
	return _repop;
}

bool RockItem::isShopItem( ) const {
	return _shop_item;
}

int RockItem::getPrice( ) const {
	return _price;
}
