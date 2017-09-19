#include "ShopItem.h"

ShopItem::ShopItem( const Vector& pos, int price ) :
Item( pos, AREA_EVENT, 64 ),
_price( price ) {
}


ShopItem::~ShopItem( ) {
}

int ShopItem::getPrice( ) {
	return _price;
}
