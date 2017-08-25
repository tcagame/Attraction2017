#pragma once
#include "NPC.h"

class NPCMermaid: public NPC {
public:
	NPCMermaid( const Vector& pos );
	virtual ~NPCMermaid( );
public:
	void setSynchronousData( ) const;
protected:
	void act( );
};