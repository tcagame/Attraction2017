#pragma once
#include "Image.h"

class ViewerStorage {
public:
	ViewerStorage( );
	virtual ~ViewerStorage( );
public:
	void draw( ) const;
private:
	ImagePtr _image;
};

