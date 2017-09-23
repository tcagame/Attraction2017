#pragma once
#include "Event.h"
#include "smart_ptr.h"

PTR( Player );
PTR( Item );

class EventRyugu : public Event {
public:
	EventRyugu( );
	virtual ~EventRyugu( );
public:
	void update( );
	void join( PLAYER target );
private:
	enum PHASE {
		PHASE_ENTER,
		PHASE_MOVE,
		PHASE_AUDIENCE,
		PHASE_FREE,
		PHASE_FINISHED,
	};
private:
	PHASE _phase;
	PlayerPtr _player;
	ItemWeakPtr _box;
	int _count;
};

