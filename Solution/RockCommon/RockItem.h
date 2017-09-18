#pragma once
#include "RockCharacter.h"
class RockItem : public RockCharacter {
public:
	RockItem( const Vector& pos, DOLL doll, int price = 0 );
	virtual ~RockItem( );
public:
	void setRepop( bool repop );
	void setShopItem( bool shop_item );
	bool isRepop( ) const;
	bool isShopItem( ) const;
	int getPrice( ) const;
	virtual double getAnimTime( ) const = 0;
protected:
	void act( );
private:
	bool _repop;
	bool _shop_item;
	int _price;
};

