#pragma once
#include "Item.h"
class ShopItem : public Item {
public:
	ShopItem( const Vector& pos, int price );
	virtual ~ShopItem( );
public:
	int getPrice( );
private:
	int _price;
};

