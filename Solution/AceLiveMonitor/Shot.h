#pragma once
#include "smart_ptr.h"
#include "Character.h"

class Shot : public Character {
public:
	Shot( const Vector& pos, DIR dir );
	virtual ~Shot( );
public:
	Chip getChip( ) const;
protected:
	void act( );
};

