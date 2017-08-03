#pragma once
#include "Image.h"


class ViewerMilitary {
public:
	ViewerMilitary( );
	virtual ~ViewerMilitary( );
public:
	void draw( ) const;
private:
	ImagePtr _image_enemy;
	ImagePtr _image_boss;
};

