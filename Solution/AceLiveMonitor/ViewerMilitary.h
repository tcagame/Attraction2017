#pragma once
#include "Image.h"


class ViewerMilitary {
public:
	ViewerMilitary( );
	virtual ~ViewerMilitary( );
public:
	void draw( ) const;
private:
	ImagePtr _enemy_midium;
	ImagePtr _enemy_wide;
	ImagePtr _enemy_boss;
};

