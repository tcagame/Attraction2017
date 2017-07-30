#pragma once
#include "Image.h"
#include <vector>


const int EVENT_PAGE_NUM = 4;

class ViewerEvent {
public:
	enum TYPE {
		TYPE_TITLE,
		TYPE_RED_DEMON,
		TYPE_SHOP = TYPE_RED_DEMON + EVENT_PAGE_NUM,
	};
public:
	ViewerEvent( );
	virtual ~ViewerEvent( );
public:
	void draw( ) const;
private:
	std::vector<ImagePtr> _images;
	ImagePtr _frame;
	TYPE _type;
};

