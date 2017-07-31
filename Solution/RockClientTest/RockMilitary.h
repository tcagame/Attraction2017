#pragma once
#include "Task.h"
#include "define.h"
#include "ModelMV1.h"
#include <string>
#include <list>
#include <array>

PTR( RockMilitary );
PTR( RockEnemy );

class RockMilitary : public Task {
public:
	static std::string getTag( ) { return "ROCKMILITARY"; };
	static RockMilitaryPtr getTask( );
public:
	RockMilitary( );
	virtual ~RockMilitary( );
public:
	void update( );
	std::list< RockEnemyPtr > getEnemyList( ) const;
private:
	std::list< RockEnemyPtr > _enemies;
	std::array< ModelMV1Ptr, MAX_DOLL > _enemy_model;
};

