#pragma once
#include "Image.h"
#include <list>

class ViewerDebug {
public:
	ViewerDebug( );
	virtual ~ViewerDebug( );
public:
	struct Data {
		struct Circle {
			Vector pos;
			double radius;
		};
		std::list< std::string > message;
		std::list< Circle > circle;
	};
public:
	void draw( );
private:
	void drawChip( );
	void pushMessageConnect( );
	void drawCircle( );
	void drawMessage( );
private:
	ImagePtr _block;
	Data _data;
};

