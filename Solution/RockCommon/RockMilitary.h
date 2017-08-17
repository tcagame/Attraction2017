#pragma once
#include "Task.h"
#include "define.h"
#include "ModelMV1.h"
#include <string>
#include <list>
#include <array>

PTR( RockMilitary );
PTR( RockEnemy );
PTR( RockImpact );

class RockMilitary : public Task {
public:
	static std::string getTag( ) { return "ROCKMILITARY"; };
	static RockMilitaryPtr getTask( );
public:
	RockMilitary( );
	virtual ~RockMilitary( );
public:
	void update( );
	void initialize( );
	std::list< RockEnemyPtr > getEnemyList( ) const;
	std::list< RockImpactPtr > getImpactList( ) const;
protected:
	void add( RockEnemyPtr enemy );
	void add( RockImpactPtr impact );
private:
	void updateEnemies( );
	void updateImpact( );
private:
	std::list< RockEnemyPtr > _enemies;
	std::list< RockImpactPtr > _impacts;
	std::array< ModelMV1Ptr, MAX_DOLL > _enemy_model;
};

