#pragma once
#include "Image.h"
#include <array>
#include "ace_define.h"

class ViewerArmoury {
public:
	ViewerArmoury( ImagePtr impact );
	virtual ~ViewerArmoury( );
public:
	void draw( ) const;
private:
	void drawShot( ) const;
	void drawImpact( ) const;
private:
	ImagePtr _image_shot;
	ImagePtr _image_impact;
};

