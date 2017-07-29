#pragma once
#include "smart_ptr.h"
#include "Image.h"
#include "ImageTarget.h"
#include <vector>

PTR( Data );
PTR( ChipCursor );
PTR( ChipEditor );
PTR( ImageTarget );
PTR( Ground );
PTR( Structure );
PTR( ChipDrawer );

class ChipPreview {
public:
	ChipPreview( DataConstPtr data, ChipCursorConstPtr chip_cursor, ChipEditorConstPtr chip_editor, ChipDrawerConstPtr chip_drawer );
	virtual ~ChipPreview( );
public:
	void update( );
	void draw( ) const;
	void drawBg( ) const;
	void drawChip( ) const;
private:
	bool _covor;
	DataConstPtr _data;
	ChipCursorConstPtr _chip_cursor;
	ChipEditorConstPtr _chip_editor;
	ChipDrawerConstPtr _chip_drawer;
	ImageTargetPtr _image;
};

