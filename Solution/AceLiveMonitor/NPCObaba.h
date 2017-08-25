#pragma once
#include "NPC.h"

class NPCObaba: public NPC {
public:
	NPCObaba( const Vector& pos );
	virtual ~NPCObaba( );
public:
	void setSynchronousData( ) const;
protected:
	void act( );
};

