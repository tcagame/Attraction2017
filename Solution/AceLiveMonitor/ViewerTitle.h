#pragma once

#include "smart_ptr.h"

PTR( Movie );

class ViewerTitle {
public:
	ViewerTitle( );
	virtual ~ViewerTitle( );

public:
	void draw( );

private:
	MoviePtr _movie;
};

