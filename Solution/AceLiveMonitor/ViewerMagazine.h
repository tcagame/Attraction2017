#pragma once
#include "Image.h"

class ViewerMagazine {
public:
	ViewerMagazine( );
	virtual ~ViewerMagazine( );
public:
	void draw( ) const;
private:
	ImagePtr _impact;
};

