#pragma once
#include "Character.h"
class NPC : public Character {
public:
	NPC( const Vector& pos, int chip_size );
	virtual ~NPC( );
public:
	virtual void damage( int force ) { };
	virtual void setSynchronousData( ) const { };
};

