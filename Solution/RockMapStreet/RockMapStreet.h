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
	};
public:
	void update( );
	void initialize( );
private:
	void updateStreet( );
	void updateCave( );
private:
	int _time;
	int _drop_time;
	RockMapStreetDrawerPtr _drawer;
	StatusPtr _status;
	STAGE _stage;
};