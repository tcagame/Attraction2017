#pragma once
#include "RockCamera.h"

class RockMapStreetCamera : public RockCamera {
public:
	RockMapStreetCamera( );
	virtual ~RockMapStreetCamera( );
public:
	void update( );
};

