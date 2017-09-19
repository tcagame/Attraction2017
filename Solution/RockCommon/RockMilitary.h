#pragma once
#include "Task.h"
#include "define.h"
#include <string>
#include <list>

PTR( RockMilitary );
PTR( RockCharacter );
PTR( RockEnemy );
PTR( RockImpact );
PTR( RockPop );

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
	void addPop( RockPopPtr pop );
	void addEnemy( RockEnemyPtr enemy );
	void addImpact( RockImpactPtr impact );
	std::list< RockEnemyPtr > getEnemyList( ) const;
	std::list< RockImpactPtr > getImpactList( ) const;
	void clean( );
	virtual void createEnemies( ) { };
	RockEnemyPtr getOverLappedEnemy( RockCharacterPtr target ) const;
private:
	void updateEnemies( );
	void updateImpact( );
	void updatePop( );
private:
	std::list< RockEnemyPtr > _enemies;
	std::list< RockImpactPtr > _impacts;
	std::list< RockPopPtr > _pops;
};

