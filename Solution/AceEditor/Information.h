#pragma once
#include "smart_ptr.h"

PTR( ChipCursor );
PTR( ObjectCursor );
PTR( Data );
PTR( ChipEditor );

class Information {
public:
	Information( DataConstPtr data, ChipCursorConstPtr chip_cursor, ObjectCursorConstPtr object_cursor, ChipEditorConstPtr chip_editor );
	virtual ~Information( );
public:
	void draw( ) const;
private:
	void drawChipMode( ) const;
	void drawObjectMode( ) const;
private:
	ChipCursorConstPtr _chip_cursor;
	ObjectCursorConstPtr _object_cursor;
	DataConstPtr _data;
	ChipEditorConstPtr _chip_editor;
};

