#pragma once
#include "Image.h"
#include "smart_ptr.h"

PTR( Data );
PTR( ObjectCursor );

class ObjectPreview {
public:
	ObjectPreview( DataConstPtr data, ObjectCursorConstPtr object_cursor, ImagePtr image_enemy, ImagePtr image_event );
	virtual ~ObjectPreview( );
public:
	void draw( ) const;
private:
	ImagePtr _block;
	ImagePtr _enemy;
	ImagePtr _event;
	ImagePtr _choise;
	DataConstPtr _data;
	ObjectCursorConstPtr _object_cursor;
};

