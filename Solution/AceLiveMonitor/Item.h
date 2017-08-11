#pragma once
#include "Character.h"
PTR( Item );

class Item:
	public Character {
public:
	Item( const Vector& pos );
	virtual ~Item( );
};

