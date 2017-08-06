#pragma once
#include "Task.h"
#include <string>
#include "ViewerEvent.h"
#include <array>

PTR( MapEvent );
const int PAGE_NUM = 8;

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
	void setType( ViewerEvent::TYPE type );
	ViewerEvent::TYPE getType( ) const;
	unsigned char getObject( const Vector& pos ) const;
	unsigned char getObject( int mx, int my ) const;
private:
	std::array< std::array< unsigned char, PAGE_NUM * PAGE_OBJECT_WIDTH_NUM * PAGE_OBJECT_WIDTH_NUM >, MAX_EVENT > _objects;
	ViewerEvent::TYPE _type;
};

