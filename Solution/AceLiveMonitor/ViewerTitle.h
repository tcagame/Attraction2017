#pragma once

#include "smart_ptr.h"

PTR( Image );

class ViewerTitle {
public:
	ViewerTitle( );
	virtual ~ViewerTitle( );

public:
	void draw( );

private:
	ImagePtr _image;
};

