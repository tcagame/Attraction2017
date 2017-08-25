#pragma once
#include "NPC.h"

class NPCShaker : public NPC {
public:
	NPCShaker( const Vector& pos );
	virtual ~NPCShaker( );
public:
	void act( );
	void damage( int force );
	void setSynchronousData( ) const;
};

