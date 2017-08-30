#pragma once

#include "Task.h"
#include "ace_define.h"
#include <string>
#include <array>

PTR( World );
PTR( Map );

class World : public Task {
public:
	static std::string getTag( ) { return "WORLD"; };
	static WorldPtr getTask( );
public:
	World( );
	virtual ~World( );
public:
	void initialize( );
	void update( );
	void setEvent( EVENT event );
	MapPtr getMap( AREA area ) const;
private:
	EVENT _event;
	MapPtr _map_street;
	std::array< MapPtr, MAX_EVENT > _map_event;
};

