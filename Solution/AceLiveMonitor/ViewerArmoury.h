#pragma once
#include "Image.h"
#include <array>
#include "ace_define.h"

class ViewerArmoury {
public:
	ViewerArmoury( );
	virtual ~ViewerArmoury( );
public:
	void draw( ) const;
private:
	ImagePtr _image_shot;
};

