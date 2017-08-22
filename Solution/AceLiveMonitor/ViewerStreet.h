#pragma once
#include "Image.h"
#include <vector>

class ViewerStreet {
public:
	ViewerStreet( );
	virtual ~ViewerStreet( );
public:
	enum LAYER {
		LAYER_BACK,
		LAYER_FRONT,
	};
public:
	void draw( LAYER layer, int sx, int sy ) const;
private:
	std::vector< ImagePtr > _images;
	int _num;
};

