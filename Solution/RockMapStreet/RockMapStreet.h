#pragma once
#include "RockMap.h"

PTR( RockMapStreetDrawer );
PTR( Status );
PTR( EventTurtle );

class RockMapStreet : public RockMap {
public:
	RockMapStreet( StatusPtr status );
	virtual ~RockMapStreet( );
public:
	enum STAGE {
		STAGE_STREET,
		STAGE_CAVE,
		STAGE_RYUGU,
	};
public:
	void update( );
	void initialize( );
private:
	void updateStreet( );
	void updateCave( );
	void updateRyugu( );
private:
	int _time;
	bool _virtue_pop;
	RockMapStreetDrawerPtr _drawer;
	StatusPtr _status;
	STAGE _stage;
};