#pragma once

#include "Task.h"
#include "mathmatics.h"
#include <string>
#include <vector>

PTR( MapStreet );

class MapStreet : public Task {
public:
	static std::string getTag( ) { return "MAP"; };
	static MapStreetPtr getTask( );
public:
	MapStreet( );
	virtual ~MapStreet( );
public:
	void update( );
	int getPageNum( ) const;
	unsigned char getObject( const Vector& pos ) const;
	unsigned char getObject( int mx, int my ) const;
	void usedObject( const Vector& pos );
private:
	void load( );
private:
	int _page_num;
	std::vector< unsigned char > _objects;
};

