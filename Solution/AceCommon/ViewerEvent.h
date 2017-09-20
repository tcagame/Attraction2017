#pragma once
#include "Image.h"
#include "ace_define.h"
#include <array>

class ViewerEvent {
public:
	ViewerEvent( );
	virtual ~ViewerEvent( );
public:
	void draw( EVENT event, int sx, int sy ) const;
private:
	std::array< ImagePtr, MAX_EVENT * EVENT_PAGE_NUM > _images;
	ImagePtr _image_escape;
};

