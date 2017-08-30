#pragma once

#include "Task.h"
#include "ace_define.h"
#include <string>

PTR( World );

class World : public Task {
public:
	static std::string getTag( ) { return "WORLD"; };
	static WorldPtr getTask( );
public:
	World( );
	virtual ~World( );
public:
	void update( );
	void setEvent( EVENT event );
private:
	EVENT _event;
};

