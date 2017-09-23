#pragma once
#include "Event.h"
#include "smart_ptr.h"

PTR( Player );

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
		PHASE_FINISHED,
	};
private:
	bool _audience;
	PHASE _phase;
	PlayerPtr _player;
	int _count;
};

