#pragma once

#include "Task.h"
#include "mathmatics.h"
#include <string>
#include <vector>

PTR( Map );

class Map : public Task {
public:
	static std::string getTag( ) { return "MAP"; };
	static MapPtr getTask( );
public:
	Map( );
	virtual ~Map( );
public:
	void update( );
	int getPageNum( ) const;
	bool isExistance( const Vector& pos ) const;
	unsigned char getObject( int mx, int my ) const;
private:
	void load( );
private:
	int _page_num;
	std::vector< unsigned char > _objects;
};

