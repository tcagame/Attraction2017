#pragma once

#include "smart_ptr.h"

PTR( Data );
PTR( ImageTarget );
PTR( Image );

class Exporter {
public:
	Exporter( DataConstPtr data );
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
	ImageTargetPtr _image_export;
};