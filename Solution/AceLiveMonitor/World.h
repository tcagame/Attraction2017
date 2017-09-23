#pragma once

#include "Task.h"
#include "ace_define.h"
#include <string>
#include <array>

PTR( World );
PTR( Map );
PTR( Player );
PTR( Event );

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
	void playMapBgm( EVENT event );
	EVENT getEvent( ) const;
	MapPtr getMap( AREA area ) const;
	void shiftPos( int map_width );
private:
	void updateEvent( );
	void updateBGM( );
	void updateVirtue( );
	void changeEvent( EVENT type );
private:
	int _virtue_pos_x;
	EventPtr _event;
	EVENT _passed_event;
	MapPtr _map_street;
	std::array< MapPtr, MAX_EVENT > _map_event;
};

