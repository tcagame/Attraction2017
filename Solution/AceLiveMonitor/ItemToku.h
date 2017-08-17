#pragma once
#include "Item.h"

class ItemToku : public Item {
public:
	ItemToku( Vector pos );
	virtual ~ItemToku( );
public:
	Chip getChip( ) const;
protected:
	void act( );
};

