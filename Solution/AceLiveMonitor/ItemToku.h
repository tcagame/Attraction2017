#pragma once
#include "Item.h"

class ItemToku : public Item {
public:
	ItemToku( Vector pos );
	virtual ~ItemToku( );
public:
	void setSynchronousData( unsigned char type, int camera_pos ) const;
protected:
	void act( );
};

