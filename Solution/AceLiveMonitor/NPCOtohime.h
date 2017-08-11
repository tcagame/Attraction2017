#pragma once
#include "Character.h"
class NPCOtohime : public Character {
public:
	NPCOtohime( const Vector& pos );
	virtual ~NPCOtohime( );
public:
	Chip getChip( ) const;
protected:
	void act( );
	void damage( int force );
};