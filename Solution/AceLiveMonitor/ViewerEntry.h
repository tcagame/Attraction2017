#pragma once

#include "ace_define.h"
#include "smart_ptr.h"

PTR( ViewrePtr );

class ViewerEntry {
public:
	ViewerEntry( );
	virtual ~ViewerEntry( );
public:
	void draw( PLAYER target );
};

