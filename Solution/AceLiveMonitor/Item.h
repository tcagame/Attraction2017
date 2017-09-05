#pragma once
#include "Character.h"
PTR( Item );

class Item:
	public Character {
public:
	Item( const Vector& pos, int chip_size = 32 );
	virtual ~Item( );
	virtual void setSynchronousData( unsigned char type, int camera_pos ) const { };
};

