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
	enum TYPE {
		TYPE_TITLE,
		TYPE_RED_DEMON,
		TYPE_FIRE = TYPE_RED_DEMON + EVENT_PAGE_NUM,
		TYPE_TREE = TYPE_FIRE + EVENT_PAGE_NUM,
		TYPE_ROCK = TYPE_TREE + EVENT_PAGE_NUM,
		TYPE_SHOP = TYPE_ROCK + EVENT_PAGE_NUM,
		TYPE_RYUGU = TYPE_SHOP + EVENT_PAGE_NUM,
		TYPE_LAKE = TYPE_RYUGU + EVENT_PAGE_NUM
	};
public:
	MapEvent( );
	virtual ~MapEvent( );
public:
	void load( );
	void update( );
	void setType( TYPE type );
	TYPE getType( ) const;
	unsigned char getObject( const Vector& pos ) const;
	unsigned char getObject( int mx, int my ) const;
private:
	std::array< std::array< unsigned char, PAGE_NUM * PAGE_OBJECT_WIDTH_NUM * PAGE_OBJECT_WIDTH_NUM >, MAX_EVENT > _objects;
	TYPE _type;
};

