#pragma once
#include "Character.h"

class NPCAngel: public Character {
public:
	NPCAngel( const Vector& pos );
	virtual ~NPCAngel( );
public:
	Chip getChip( ) const;
protected:
	void act( );
	void damage( int force );
};