#pragma once

#include "Image.h"
#include "ace_define.h"
#include <array>

class ViewerStatus {
public:
	ViewerStatus( );
	virtual ~ViewerStatus( );
public:
	void draw( PLAYER player, int sx, int sy ) const;
private:
	void drawBustup( PLAYER player, int sx, int sy ) const;
	void drawPower( int power, int sx, int sy ) const;
	void drawMoney( int money, int sx, int sy ) const;
	void drawVirtue( int virtue, int sx, int sy ) const;
	void playSe( PLAYER player ) const;
private:
	ImagePtr _image_frame;
	ImagePtr _status_ui;
	std::array< ImagePtr, MAX_PLAYER > _image_bustup;
};

