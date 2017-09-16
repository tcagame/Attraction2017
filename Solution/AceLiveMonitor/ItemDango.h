#pragma once
#include "ShopItem.h"

class ItemDango : public ShopItem {
public:
	ItemDango( const Vector& pos );
	virtual ~ItemDango( );
public:
	void setSynchronousData( int camera_pos ) const;
protected:
	void act( );
};

