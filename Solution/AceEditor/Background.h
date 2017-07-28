#pragma once
#include <map>
#include "smart_ptr.h"

PTR( Image );

class Background {
public:
	Background( );
	virtual ~Background( );
public:
	bool loadImage( std::string directory, std::string filename );
	ImagePtr getImage( std::string filename );
private:
	std::map< std::string, ImagePtr > _bg;
};

