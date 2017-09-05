#pragma once
#include "ShopItem.h"
class ItemEnhancedAttack : public ShopItem {
public:
	ItemEnhancedAttack( const Vector& pos );
	virtual ~ItemEnhancedAttack( );
public:
	void setSynchronousData( unsigned char type, int camera_pos ) const;
protected:
	void act( );
};

