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
		MAX_STAGE
	};
public:
	void update( );
	void initialize( );
	STAGE getStage( ) const;
private:
	void updateStreet( );
	void updateCave( );
	void updateRyugu( );
	void loadStage( STAGE next );
	void genarateEnemies( STAGE next );
	void genarateStorage( STAGE next );
	void genarateEventCharacters( STAGE next );
	void resetFamilyPos( STAGE next );
	bool isInActivePlayer( );
private:
	int _time;
	bool _virtue_pop;
	RockMapStreetDrawerPtr _drawer;
	StatusPtr _status;
	STAGE _stage;
};