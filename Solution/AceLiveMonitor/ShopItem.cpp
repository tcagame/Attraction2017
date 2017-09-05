#include "ShopItem.h"



ShopItem::ShopItem( const Vector& pos, int price ) :
Item( pos, 64 ),
_price( price ) {
}


ShopItem::~ShopItem( ) {
}

int ShopItem::getPrice( ) {
	return _price;
}
