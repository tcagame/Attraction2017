#pragma once
#include "Image.h"
#include <array>
#include "ace_define.h"

class ViewerStreet {
public:
	ViewerStreet( );
	virtual ~ViewerStreet( );
public:
	void draw( double camera_pos ) const;
private:
	std::array< ImagePtr, ACE_MAP_NUM > _image_back;
	std::array< ImagePtr, ACE_MAP_NUM > _image_front;
};

