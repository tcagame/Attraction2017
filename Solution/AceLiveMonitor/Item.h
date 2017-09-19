#pragma once
#include "Character.h"
PTR( Item );

class Item:
	public Character {
public:
	Item( const Vector& pos, int chip_size = 32, bool mass = true );
	virtual ~Item( );
	virtual void setSynchronousData( int camera_pos ) const { };
};

