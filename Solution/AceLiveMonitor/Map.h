#pragma once

#include "smart_ptr.h"
#include "mathmatics.h"
#include <vector>
#include <string>

PTR( Map );

class Map {
public:
	Map( std::string filename );
	virtual ~Map( );
public:
	int getPageNum( ) const;
	unsigned char getObject( const Vector& pos ) const;
	unsigned char getObject( int mx, int my ) const;
private:
	int _page_num;
	std::vector< unsigned char > _objects;
};

