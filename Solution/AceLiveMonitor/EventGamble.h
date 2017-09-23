#pragma once
#include "Event.h"
#include "smart_ptr.h"

PTR( Player );

class EventGamble: public Event {
public:
	EventGamble( );
	virtual ~EventGamble( );
public:
	void update( );
	void join( PLAYER target );
private:
	enum PHASE {
		PHASE_AUDIENCE,
		PHASE_BET,
		PHASE_DICE,
		PHASE_SUCCESS,
		PHASE_FINISHED,
	};
private:
	PlayerPtr _player;
	PHASE _phase;
	int _count;
	bool _odd;
};

