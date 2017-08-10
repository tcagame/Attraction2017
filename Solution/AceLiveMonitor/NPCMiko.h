#pragma once
#include "Character.h"

class NPCMiko: public Character {
public:
	NPCMiko( const Vector& pos );
	virtual ~NPCMiko( );
public:
	Chip getChip( ) const;
protected:
	void act( );
	void damage( int force );
};

