#pragma once
#include "Item.h"

class ItemVirtue : public Item {
public:
	ItemVirtue( Vector pos );
	virtual ~ItemVirtue( );
public:
	void setSynchronousData( unsigned char type, int camera_pos ) const;
protected:
	void act( );
};

