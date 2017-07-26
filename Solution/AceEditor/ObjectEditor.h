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
	void setObject( unsigned char object );
	unsigned char getObject( ) const;
	void save( ) const;
	void load( );
private:
	unsigned char _object;
	bool _click_active;
	DataPtr _data;
	ObjectCursorConstPtr _object_cursor;
};

