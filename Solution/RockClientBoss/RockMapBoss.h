#pragma once
#include "RockMap.h"
#include "mathmatics.h"

PTR( RockMapBossDrawer );
PTR( Status );

class RockMapBoss : public RockMap {
public:
	RockMapBoss( StatusPtr status );
	virtual ~RockMapBoss( );
public:
	enum STAGE {
		STAGE_FIRE,
		STAGE_FIRE_TO_ROCK,
		STAGE_ROCK,
		STAGE_ROCK_TO_TREE,
		STAGE_TREE,
		STAGE_TREE_TO_FIRE,
		MAX_STAGE
	};
public:
	void update( );
	void initialize( );
	STAGE getStage( ) const;
private:
	bool isWarpToBoss( const Vector& pos );
	bool isWarpToStreet( STAGE stage );
private:
	RockMapBossDrawerPtr _drawer;
	StatusPtr _status;
};

