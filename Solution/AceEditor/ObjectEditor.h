#pragma once
#include "smart_ptr.h"

PTR( Data );
PTR( ObjectCursor );

class ObjectEditor {
public:
	ObjectEditor( DataPtr data, ObjectCursorConstPtr object_cursor );
	virtual ~ObjectEditor( );
public:
	void update( );
	void save( ) const;
	void load( );
private:
	DataPtr _data;
	ObjectCursorConstPtr _object_cursor;
};

