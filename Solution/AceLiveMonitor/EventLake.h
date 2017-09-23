#pragma once
#include "Event.h"
#include "smart_ptr.h"

PTR( NPCMiko );
PTR( Player );

class EventLake : public Event {
public:
	EventLake( );
	virtual ~EventLake( );
public:
	void update( );
	void join( PLAYER target );
private:
	enum PHASE {
		PHASE_ENTER,
		PHASE_MOVE,
		PHASE_AUDIENCE,
		PHASE_FINISHED,
	};
private:
	int _count;
	PHASE _phase;
	PlayerPtr _player;
	NPCMikoPtr _npc;
};

