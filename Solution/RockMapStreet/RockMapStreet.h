#pragma once
#include "RockMap.h"

PTR( RockMapStreetDrawer );
PTR( Status );

class RockMapStreet : public RockMap {
public:
	RockMapStreet( StatusPtr status );
	virtual ~RockMapStreet( );
public:
	enum STAGE {
		STAGE_STREET,
		STAGE_CAVE,
		STAGE_TOKU
	};
public:
	void update( );
	void initialize( );
private:
	void updateStreet( );
	void updateCave( );
	void updateToku( );
private:
	int _time;
	RockMapStreetDrawerPtr _drawer;
	StatusPtr _status;
};