#pragma once
#include "Item.h"

class ItemFire: public Item {
public:
	ItemFire( const Vector& pos );
	virtual ~ItemFire( );
public:
	void setSynchronousData( int camera_pos ) const;
protected:
	void act( );
}; 

