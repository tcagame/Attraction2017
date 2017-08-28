#pragma once
#include "RockMapStreet.h"

class RockMapStreetDrawer {
public:
	RockMapStreetDrawer( RockMapStreet::STAGE stage );
	virtual ~RockMapStreetDrawer( );
public:
	void draw( ) const;
	RockMapStreet::STAGE getStage( ) const;
private:
	RockMapStreet::STAGE _stage;
};

