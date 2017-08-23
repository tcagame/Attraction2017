#pragma once
#include "Item.h"

class ItemTree: public Item {
public:
	ItemTree( const Vector& pos );
	virtual ~ItemTree( );
public:
	void setSynchronousData( unsigned char type, int camera_pos ) const;
protected:
	void act( );
}; 

