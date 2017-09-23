#pragma once
#include "Event.h"
#include "smart_ptr.h"

PTR( Player );

class EventBudha : public Event {
public:
	EventBudha( );
	virtual ~EventBudha( );
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
	int _count;
	PHASE _phase;
	PlayerPtr _player;
};

