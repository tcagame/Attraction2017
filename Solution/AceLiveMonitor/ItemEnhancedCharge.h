#pragma once
#include "ShopItem.h"
class ItemEnhancedCharge : public ShopItem {
public:
	ItemEnhancedCharge( const Vector& pos );
	virtual ~ItemEnhancedCharge( );
public:
	void setSynchronousData( int camera_pos ) const;
protected:
	void act( );
};

