#pragma once
#include "Task.h"
#include <string>
#include <list>

PTR( RockArmoury );
PTR( RockShot );

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
	int getEffectChargeId( ) const;
	int getEffectShotId( ) const;
	std::list< RockShotPtr > getShots( ) const;
private:
	int _shot_id;
	int _charge_id;
	std::list< RockShotPtr > _shots;
};

