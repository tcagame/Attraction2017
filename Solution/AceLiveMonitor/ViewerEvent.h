#pragma once
#include "Image.h"
#include <vector>
#include "ace_define.h"

class ViewerEvent {
public:
	enum TYPE {
		TYPE_TITLE,
		TYPE_RED_DEMON,
		TYPE_FIRE = TYPE_RED_DEMON + EVENT_PAGE_NUM,
		TYPE_TREE = TYPE_FIRE + EVENT_PAGE_NUM,
		TYPE_ROCK = TYPE_TREE + EVENT_PAGE_NUM,
		TYPE_SHOP = TYPE_ROCK + EVENT_PAGE_NUM,
	};
public:
	ViewerEvent( );
	virtual ~ViewerEvent( );
public:
	void draw( ) const;
private:
	std::vector< ImagePtr > _images;
	ImagePtr _frame;
};

