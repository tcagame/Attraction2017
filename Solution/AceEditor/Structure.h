#pragma once
#include "Image.h"
#include "ace_define.h"
#include <array>

class Structure
{
public:
	Structure();
	virtual ~Structure();
public:
	ImagePtr getImage( int idx ) const;
	int getSize( ) const;
private:
	std::array< ImagePtr, STRUCTURE_LIST_NUM > _image;
};

