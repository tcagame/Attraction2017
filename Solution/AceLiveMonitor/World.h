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
private:
	void setEvent( EVENT event );
	void updateEvent( );
	void onEvent( );
	void onEventReddaemon( PlayerPtr player );
	void onEventFlame( PlayerPtr player );
	void onEventWood( PlayerPtr player );
	void onEventMineral( PlayerPtr player );
	void onEventShop( PlayerPtr player );
	void onEventRyugu( PlayerPtr player );
	void onEventLake( PlayerPtr player );
	void onEventCall( PlayerPtr player );
	void onEventGamble( PlayerPtr player );
private:
	EventPtr _event;
	MapPtr _map_street;
	std::array< MapPtr, MAX_EVENT > _map_event;
};

