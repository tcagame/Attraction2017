#pragma once
#include "Image.h"
#include <vector>
#include "ace_define.h"

class ViewerEvent {
public:
	ViewerEvent( );
	virtual ~ViewerEvent( );
public:
	void draw( ) const;
private:
	std::vector< ImagePtr > _images;
	ImagePtr _frame;
	ImagePtr _characters;
};

