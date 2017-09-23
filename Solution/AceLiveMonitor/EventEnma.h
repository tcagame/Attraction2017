#pragma once
#include "Event.h"
#include "smart_ptr.h"

PTR( Player );

class EventEnma : public Event {
public:
	EventEnma( );
	virtual ~EventEnma( );
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
};

