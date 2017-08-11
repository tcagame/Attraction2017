#pragma once
#include "Item.h"
class ItemFire: public Item {
public:
	ItemFire( const Vector& pos );
	virtual ~ItemFire( );
public:
	Chip getChip( ) const;
protected:
	void act( );
}; 

