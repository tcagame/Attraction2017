#pragma once

#include "smart_ptr.h"

PTR( Data );
PTR( ImageTarget );
PTR( Image );
PTR( ChipDrawer );

class Exporter {
public:
	Exporter( DataConstPtr data, ChipDrawerConstPtr chip_drawer );
	virtual ~Exporter( );
public:
	void start( );
	bool update( );
	void draw( );
private:
	DataConstPtr _data;
	int _max;
	int _now;
	ImagePtr _image_progress;
	ImageTargetPtr _image_export_front;
	ImageTargetPtr _image_export_back;
	ChipDrawerConstPtr _chip_drawer;
};