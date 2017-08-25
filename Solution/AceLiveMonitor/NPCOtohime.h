#pragma once
#include "NPC.h"

class NPCOtohime : public NPC {
public:
	NPCOtohime( const Vector& pos );
	virtual ~NPCOtohime( );
public:
	void setSynchronousData( ) const;
protected:
	void act( );
};