#pragma once
#include "RockCamera.h"
#include "RockMapStreet.h"
#include <array>

PTR( RockMapStreet );

class RockMapStreetCamera : public RockCamera {
public:
	RockMapStreetCamera( );
	virtual ~RockMapStreetCamera( );
private:
	void setCamera( );
private:
	std::array< Vector, RockMapStreet::MAX_STAGE > _dir;
	std::array< double, RockMapStreet::MAX_STAGE > _length;
};

