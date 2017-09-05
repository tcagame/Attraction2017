#pragma once

#include "ace_define.h"
#include "smart_ptr.h"

PTR( Image );

class ViewerProgress {
public:
	ViewerProgress();
	virtual ~ViewerProgress();
public:
	void draw( PLAYER target );
private:
	ImagePtr _image_frame;
	ImagePtr _image_bar;
};

