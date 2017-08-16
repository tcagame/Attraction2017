#pragma once
#include "Image.h"

class ViewerStatus {
public:
	ViewerStatus( );
	virtual ~ViewerStatus( );
public:
	void draw( ) const;
	void drawHp( ) const;
private:
	ImagePtr _status_flame;
	ImagePtr _status_ui;
};

