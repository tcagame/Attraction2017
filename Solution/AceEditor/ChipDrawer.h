#pragma once
#include "smart_ptr.h"

PTR( Ground );
PTR( Structure );
PTR( Image );
PTR( Data );

class ChipDrawer {
public:
	ChipDrawer( DataConstPtr data, GroundConstPtr ground, StructureConstPtr structure );
	virtual ~ChipDrawer( );
public:
	void draw( int mx, int my, int gx, int gy, bool select = false ) const;
private:
	ImagePtr _image_choice_front;
	ImagePtr _image_choice_back;
	int _width_num;
	DataConstPtr _data;
	GroundConstPtr _ground;
	StructureConstPtr _structure;
};