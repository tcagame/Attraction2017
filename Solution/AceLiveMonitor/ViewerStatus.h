#pragma once
#include "Image.h"

class ViewerStatus {
public:
	ViewerStatus( );
	virtual ~ViewerStatus( );
public:
	void draw( ) const;
private:
	void drawHp( ) const;
	void drawMoney( ) const;
	void drawToku( ) const;
private:
	ImagePtr _status_flame;
	ImagePtr _status_ui;
};

