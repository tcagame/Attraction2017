#pragma once

#include "Event.h"
#include "smart_ptr.h"

PTR( Player );

class EventCall : public Event {
public:
	EventCall( );
	virtual ~EventCall( );
public:
	void update( );
	void join( PLAYER target );
private:
	enum PHASE {
		PHASE_ENTER,
		PHASE_MOVE,
		PHASE_CALL,
		PHASE_FINISHED,
	};
private:
	int _count;
	PHASE _phase;
	PlayerPtr _player;
};

