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

class ChipPreview {
public:
	ChipPreview( DataConstPtr data, ChipCursorConstPtr chip_cursor, ChipEditorConstPtr chip_editor, GroundConstPtr ground, StructureConstPtr structure );
	virtual ~ChipPreview( );
public:
	void update( );
	void draw( ) const;
private:
	bool _covor;
	DataConstPtr _data;
	ChipCursorConstPtr _chip_cursor;
	ChipEditorConstPtr _chip_editor;
	ImageTargetPtr _image_background;
	ImagePtr _image_choice_front;
	ImagePtr _image_choice_back;
	GroundConstPtr _ground;
	StructureConstPtr _structure;
};

