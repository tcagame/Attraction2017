#pragma once
#include "smart_ptr.h"
#include "ace_define.h"
#include <array>

PTR( Data );
PTR( ChipCursor );
PTR( ChipEditor );
PTR( Image );

class ChipGuide {
public:
	ChipGuide( DataConstPtr data, ChipCursorConstPtr chip_cursor, ChipEditorConstPtr chip_editor );
	virtual ~ChipGuide( );
public:
	void update( );
	void draw( ) const;
private:
	std::array< bool, STRUCTURE_LIST_NUM > _struct_graph_data;
	std::array< bool, GROUND_LIST_NUM > _ground_graph_data;
	DataConstPtr _data;
	ChipCursorConstPtr _chip_cursor;
	ChipEditorConstPtr _chip_editor;
	ImagePtr _image_chip_guide;
};

