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
	void drawItem( PLAYER player, int sx, int sy ) const;
	void drawVirtue( int virtue, int sx, int sy ) const;
	void drawRedo( int redo, int sx, int sy ) const;
private:
	ImagePtr _image_frame;
	std::array< ImagePtr, MAX_PLAYER > _image_bustup;
	std::array< ImagePtr, MAX_PLAYER > _image_name;
	std::array< ImagePtr, 16 > _image_power;
	std::array< ImagePtr, 7 > _image_item;
	ImagePtr _image_virtue;
	ImagePtr _image_virtue_number;
	ImagePtr _image_money_number;
	ImagePtr _image_item_effect;
	ImagePtr _image_redo;
};

