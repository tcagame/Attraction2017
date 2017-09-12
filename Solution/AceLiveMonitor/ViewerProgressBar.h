#pragma once

#include "ace_define.h"
#include "smart_ptr.h"

PTR( Image );

class ViewerProgressBar {
public:
	ViewerProgressBar();
	virtual ~ViewerProgressBar();
public:
	void draw( PLAYER target );
private:
	ImagePtr _image_bar;
};

