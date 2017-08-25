#pragma once
#include "NPC.h"

class NPCAngel: public NPC {
public:
	NPCAngel( const Vector& pos );
	virtual ~NPCAngel( );
public:
	void setSynchronousData( ) const;
protected:
	void act( );
};