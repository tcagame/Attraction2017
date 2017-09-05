#pragma once
#include "ShopItem.h"
class ItemEnhancedCharge : public ShopItem {
public:
	ItemEnhancedCharge( const Vector& pos );
	virtual ~ItemEnhancedCharge( );
public:
	void setSynchronousData( unsigned char type, int camera_pos ) const;
protected:
	void act( );
};

