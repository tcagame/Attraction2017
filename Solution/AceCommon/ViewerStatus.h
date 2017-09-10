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
	void drawVirtue( int virtue, int sx, int sy ) const;
private:
	ImagePtr _image_frame;
	std::array< ImagePtr, MAX_PLAYER > _image_bustup;
	std::array< ImagePtr, MAX_PLAYER > _image_name;
	std::array< ImagePtr, 16 > _image_power;
};

