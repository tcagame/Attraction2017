#pragma once

#include "ace_define.h"
#include "Image.h"
#include <array>

class ViewerObject {
public:
	ViewerObject();
	virtual ~ViewerObject( );
public:
	void draw( AREA area, int sx, int sy ) const;
private:
	enum GRAPH {
		GRAPH_PLAYER_TAROSUKE,
		GRAPH_PLAYER_TAROJIRO,
		GRAPH_PLAYER_GARISUKE,
		GRAPH_PLAYER_TAROMI,
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
	void drawSprite( int x, int y, unsigned char type, unsigned char attribute, int pattern ) const;
	Sprite getSpritePlayerWait( GRAPH graph, int x, int y, unsigned char attribute, int pattern ) const;
private:
	std::array< ImagePtr, MAX_GRAPH > _image;
};

