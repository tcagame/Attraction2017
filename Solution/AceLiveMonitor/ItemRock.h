#pragma once
#include "Item.h"

class ItemRock: public Item {
public:
	ItemRock( const Vector& pos );
	virtual ~ItemRock( );
public:
	void setSynchronousData( int camera_pos ) const;
protected:
	void act( );
}; 

