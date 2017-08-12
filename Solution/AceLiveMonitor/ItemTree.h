#pragma once
#include "Item.h"
class ItemTree: public Item {
public:
	ItemTree( const Vector& pos );
	virtual ~ItemTree( );
public:
	Chip getChip( ) const;
protected:
	void act( );
}; 

