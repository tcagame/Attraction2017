#pragma once
#include "Image.h"
#include <vector>

class Structure
{
public:
	Structure();
	virtual ~Structure();
public:
	ImagePtr getImage( int idx ) const;
	int getSize( ) const;
private:
	std::vector< ImagePtr > _image;
};

