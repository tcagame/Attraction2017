#pragma once
#include "Image.h"

class ViewerEvent {
public:
	ViewerEvent( );
	virtual ~ViewerEvent( );
public:
	void draw( ) const;
private:
	ImagePtr _title;
	ImagePtr _frame;
};

