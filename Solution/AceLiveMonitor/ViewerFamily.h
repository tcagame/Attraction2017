#pragma once
#include <array>
#include "Image.h"
#include "ace_define.h"

class ViewerFamily {
public:
	ViewerFamily( );
	virtual ~ViewerFamily( );
public:
	void draw( ) const;
private:
	std::array< ImagePtr, MAX_PLAYER > _image;
	ImagePtr _shot;
};

