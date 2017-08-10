#pragma once
#include "Character.h"

class NPCObaba: public Character {
public:
	NPCObaba( const Vector& pos );
	virtual ~NPCObaba( );
public:
	Chip getChip( ) const;
protected:
	void act( );
	void damage( int force );
};

