#pragma once
#include "Image.h"
#include <array>
#include "ace_define.h"

class ViewerShot {
public:
	ViewerShot( );
	virtual ~ViewerShot( );
public:
	void draw( ) const;
private:
	ImagePtr _image;
};

