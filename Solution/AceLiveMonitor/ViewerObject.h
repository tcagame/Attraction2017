#pragma once

#include "Image.h"
#include <array>

class ViewerObject {
public:
	ViewerObject();
	virtual ~ViewerObject( );
public:
	void drawMain( ) const;
	void drawEvent( ) const;
private:
	enum GRAPH {

		MAX_GRAPH,
	};
	struct Sprite {
		GRAPH graph;
		int tx;
		int ty;
		int tw;
		int th;
		int sx1;
		int sy1;
		int sx2;
		int sy2;
	};
private:
	void draw( int idx ) const;
private:
	std::array< ImagePtr, MAX_GRAPH > _image;
};

