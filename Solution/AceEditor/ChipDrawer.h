#pragma once
#include "smart_ptr.h"

PTR( Ground );
PTR( Structure );
PTR( Background );
PTR( Image );
PTR( Data );

class ChipDrawer {
public:
	ChipDrawer( DataConstPtr data, GroundConstPtr ground, StructureConstPtr structure, BackgroundPtr background );
	virtual ~ChipDrawer( );
public:
	void drawChip( int mx, int my, int gx, int gy, bool select = false ) const;
	void drawBg( int screen_page, int scroll_mx ) const;
private:
	ImagePtr _image_choice_front;
	ImagePtr _image_choice_back;
	int _width_num;
	DataConstPtr _data;
	GroundConstPtr _ground;
	StructureConstPtr _structure;
	BackgroundPtr _background;
};