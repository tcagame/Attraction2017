#pragma once
#include "Item.h"

class ItemRock: public Item {
public:
	ItemRock( const Vector& pos );
	virtual ~ItemRock( );
public:
	Chip getChip( ) const;
protected:
	void act( );
}; 

