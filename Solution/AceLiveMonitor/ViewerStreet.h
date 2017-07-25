#pragma once
#include "Image.h"
#include "ace_define.h"
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
	void draw( LAYER layer ) const;
private:
	std::vector< ImagePtr > _images;
	int _num;
};

