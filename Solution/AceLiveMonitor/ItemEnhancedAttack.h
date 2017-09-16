#pragma once
#include "ShopItem.h"
class ItemEnhancedAttack : public ShopItem {
public:
	ItemEnhancedAttack( const Vector& pos );
	virtual ~ItemEnhancedAttack( );
public:
	void setSynchronousData( int camera_pos ) const;
protected:
	void act( );
};

