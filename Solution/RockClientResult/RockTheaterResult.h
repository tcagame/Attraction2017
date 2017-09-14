#pragma once
#include "RockTheater.h"
#include <vector>

PTR( Status );
PTR( ImageTarget );

class RockTheaterResult : public RockTheater {
public:
	RockTheaterResult( StatusPtr status );
	virtual ~RockTheaterResult( );
public:
	void initialize( );
	void update( );
private:
	void createImage( );
private:
	bool _play;
	std::vector< ImagePtr > _images;
	ImageTargetPtr _draw_image;
	StatusPtr _status;
};

