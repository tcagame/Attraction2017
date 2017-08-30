#pragma once
#include "RockMap.h"
#include "mathmatics.h"

PTR( RockMapBossDrawer );

class RockMapBoss : public RockMap {
public:
	RockMapBoss( );
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
private:
	bool isWarp( const Vector& pos );
private:
	RockMapBossDrawerPtr _drawer;
};
