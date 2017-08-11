#pragma once
#include "Character.h"

class NPCMermaid: public Character {
public:
	NPCMermaid( const Vector& pos );
	virtual ~NPCMermaid( );
public:
	Chip getChip( ) const;
protected:
	void act( );
	void damage( int force );
};