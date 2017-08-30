#pragma once
#include "RockMap.h"

PTR( RockMapStreetDrawer );
PTR( Status );

class RockMapStreet : public RockMap {
public:
	RockMapStreet( StatusPtr status );
	virtual ~RockMapStreet( );
public:
	enum STATE {
		STATE_STREET,
		STATE_CAVE,
		STATE_TOKU,
	};
	enum STAGE {
		STAGE_STREET,
		STAGE_CAVE,
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
	STATE _state;
};