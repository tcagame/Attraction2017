#pragma once
#include "NPC.h"

class NPCMiko: public NPC {
public:
	NPCMiko( const Vector& pos );
	virtual ~NPCMiko( );
public:
	void setSynchronousData( ) const;
	void startSolt( );
protected:
	void act( );
private:
	bool _solt;
};

