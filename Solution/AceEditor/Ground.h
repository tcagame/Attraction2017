#pragma once
#include "Image.h"
#include <vector>

class Ground {
public:
	Ground( );
	virtual ~Ground( );
public:
	ImagePtr getImage( int idx ) const;
	int getSize( ) const;
private:
	std::vector< ImagePtr > _image;
};

