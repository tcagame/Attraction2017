#pragma once
#include "Image.h"

class ViewerStatus {
public:
	ViewerStatus( );
	virtual ~ViewerStatus( );
public:
	void draw( ) const;
private:
	ImagePtr _status_flame;
};

