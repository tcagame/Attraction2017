#pragma once
#include <array>
#include "Image.h"
#include "ace_define.h"

class ViewerFamily {
public:
	ViewerFamily( );
	virtual ~ViewerFamily( );
public:
	void draw( ) const;
private:
	std::array< ImagePtr, ACE_PLAYER_NUM > _image;
};

