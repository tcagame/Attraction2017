#pragma once
#include "Task.h"
#include <string>
#include <list>

PTR( RockArmoury );
PTR( RockShot );
PTR( RockShotPlayer );
PTR( RockEnemy );

class RockArmoury : public Task {
public:
	static std::string getTag( ) { return "ROCKARMOURY"; };
	static RockArmouryPtr getTask( );
public:
	RockArmoury( );
	virtual ~RockArmoury( );
public:
	void initialize( );
	void update( );
	void addShot( RockShotPtr shot );
	std::list< RockShotPtr > getShots( ) const;
private:
	RockEnemyPtr getOverLappedEnemy( RockShotPtr shot ) const;
private:
	std::list< RockShotPtr > _shots;
};

