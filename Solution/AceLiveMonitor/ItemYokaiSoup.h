#pragma once
#include "ShopItem.h"
class ItemYokaiSoup : public ShopItem {
public:
	ItemYokaiSoup( const Vector& pos );
	virtual ~ItemYokaiSoup( );
public:
	void setSynchronousData( int camera_pos ) const;
protected:
	void act( );
};

