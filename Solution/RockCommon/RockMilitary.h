#pragma once
#include "Task.h"
#include "define.h"
#include <string>
#include <list>

PTR( RockMilitary );
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
	void add( RockEnemyPtr enemy );
	std::list< RockEnemyPtr > getEnemyList( ) const;
	std::list< RockImpactPtr > getImpactList( ) const;
	void clean( );
protected:
	void add( RockImpactPtr impact );
private:
	void updateEnemies( );
	void updateImpact( );
	void updatePop( );
private:
	std::list< RockEnemyPtr > _enemies;
	std::list< RockImpactPtr > _impacts;
	std::list< RockPopPtr > _pops;
};

