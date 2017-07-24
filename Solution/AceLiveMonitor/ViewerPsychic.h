#pragma once
#include "Image.h"
#include <array>
#include "ace_define.h"

class ViewerPsychic {
public:
	ViewerPsychic( );
	virtual ~ViewerPsychic( );
public:
	void draw( ) const;
private:
	ImagePtr _image;
};

