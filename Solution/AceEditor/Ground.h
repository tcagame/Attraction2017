#pragma once
#include "Image.h"
#include "ace_define.h"
#include <array>

class Ground {
public:
	Ground( );
	virtual ~Ground( );
public:
	ImagePtr getImage( int idx ) const;
	int getSize( ) const;
private:
	std::array< ImagePtr, GROUND_LIST_NUM > _image;
};

