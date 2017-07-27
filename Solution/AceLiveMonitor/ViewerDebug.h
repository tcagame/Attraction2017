#pragma once
#include "Image.h"

class ViewerDebug {
public:
	ViewerDebug( );
	virtual ~ViewerDebug( );
public:
	void draw( ) const;
private:
	ImagePtr _block;
};

