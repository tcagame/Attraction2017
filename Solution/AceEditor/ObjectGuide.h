#pragma once
#include "smart_ptr.h"

PTR( ObjectCursor );
PTR( Data );
PTR( Image );

class ObjectGuide {
public:
	ObjectGuide( ObjectCursorConstPtr object_cursor );
	virtual ~ObjectGuide( );
public:
	void update( );
	void draw( ) const;
private:
	ObjectCursorConstPtr _object_cursor;
	ImagePtr _image;
};

