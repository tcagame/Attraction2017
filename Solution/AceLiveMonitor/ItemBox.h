#pragma once
#include "Item.h"

class ItemBox : public Item {
public:
	ItemBox( );
	virtual ~ItemBox( );
protected:
	void act( );
	void setSynchronousData( int camera_pos ) const;
};

