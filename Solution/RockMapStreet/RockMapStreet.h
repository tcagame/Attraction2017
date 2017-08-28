#pragma once
#include "RockMap.h"

PTR( RockMapStreetDrawer );

class RockMapStreet : public RockMap {
public:
	RockMapStreet( );
	virtual ~RockMapStreet( );
public:
	enum STAGE {
		STAGE_STREET,
		STAGE_CAVE
	};
public:
	void update( );
	void initialize( );
private:
	void updateStreet( );
	void updateCave( );
private:
	int _time;
	RockMapStreetDrawerPtr _drawer;
};