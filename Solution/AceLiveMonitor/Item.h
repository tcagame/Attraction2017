#pragma once
#include "Character.h"
PTR( Item );

class Item : public Character {
public:
	Item( const Vector& pos, AREA area, int chip_size = 32 );
	virtual ~Item( );
public:
	void setDrop( );
	virtual void setSynchronousData( int camera_pos ) const { };
};

