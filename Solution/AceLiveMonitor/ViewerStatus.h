#pragma once
#include "Image.h"
#include "ace_define.h"

class ViewerStatus {
public:
	ViewerStatus( );
	virtual ~ViewerStatus( );
public:
	void draw( PLAYER player, int sx, int sy ) const;
private:
	void drawPower( int power, int sx, int sy ) const;
	void drawMoney( int money, int sx, int sy ) const;
	void drawVirtue( int virtue, int sx, int sy ) const;
private:
	ImagePtr _status_flame;
	ImagePtr _status_ui;
};

