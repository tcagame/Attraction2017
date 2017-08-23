#pragma once
#include "Item.h"

class ItemRock: public Item {
public:
	ItemRock( const Vector& pos );
	virtual ~ItemRock( );
public:
	void setSynchronousData( unsigned char type, int camera_pos ) const;
protected:
	void act( );
}; 

