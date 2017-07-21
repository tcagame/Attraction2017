#pragma once
#include "Image.h"
#include "smart_ptr.h"

PTR( Data );
PTR( ObjectCursor );

class ObjectPreview {
public:
	ObjectPreview( DataConstPtr data, ObjectCursorConstPtr object_cursor );
	virtual ~ObjectPreview( );
public:
	void draw( ) const;
private:
	ImagePtr _block;
	DataConstPtr _data;
	ObjectCursorConstPtr _object_cursor;
};

