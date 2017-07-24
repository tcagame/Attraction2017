#pragma once
#include "smart_ptr.h"
#include "Image.h"
#include <array>
#include "ace_define.h"

PTR( ViewerFamily );
PTR( ViewerStreet );
PTR( ViewerPsychic );


class Viewer {
public:
	Viewer( );
	virtual ~Viewer( );
public:
	void update( );
private:
	ViewerFamilyConstPtr _viewer_family;
	ViewerStreetConstPtr _viewer_street;
	ViewerPsychicConstPtr _viewer_psychic;
};

