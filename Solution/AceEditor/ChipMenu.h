#pragma once
#include "smart_ptr.h"
#include "mathmatics.h"
#include "ace_define.h"
#include <array>

PTR( ChipEditor );
PTR( Image );
PTR( Ground );
PTR( Structure );

class ChipMenu {
public:
	ChipMenu( ImagePtr menu_image, ChipEditorPtr chip_editor, GroundConstPtr ground, StructureConstPtr structure );
	virtual ~ChipMenu( );
public:
	void update( );
	void draw( ) const;
	void setPos( const Vector& pos );
	bool getActive( ) const;
private:
	enum TAG {
		TAG_GROUND,
		TAG_STRUCTURE,
		TAG_HEIGHT,
		MAX_TAG
	};
private:
	bool _active;
	ChipEditorPtr _chip_editor;
	Vector _pos;
	TAG _select_tag;
	int _ground_page_num;
	int _structure_page_num;
	std::array< GRAPH, GROUND_LIST_NUM	  > _graph_ground;
	std::array< GRAPH, STRUCTURE_LIST_NUM > _graph_structure;
	int _page;
	ImagePtr _image;
	GroundConstPtr _ground;
	StructureConstPtr _structure;
};

