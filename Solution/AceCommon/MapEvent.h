#pragma once
#include "Task.h"
#include <string>
#include "ViewerEvent.h"
#include <array>

PTR( MapEvent );

class MapEvent : public Task {
public:
	static std::string getTag( ) { return "MAPEVENT"; };
	static MapEventPtr getTask( );
public:
	MapEvent( );
	virtual ~MapEvent( );
public:
	void load( );
	void update( );
	void setEvent( EVENT event );
	EVENT getEvent( ) const;
	unsigned char getObject( const Vector& pos ) const;
	unsigned char getObject( int mx, int my ) const;
private:
	std::array< std::array< unsigned char, ACE_MAP_SIZE * PAGE_OBJECT_WIDTH_NUM * PAGE_OBJECT_WIDTH_NUM >, MAX_EVENT > _objects;
	EVENT _event;
};

