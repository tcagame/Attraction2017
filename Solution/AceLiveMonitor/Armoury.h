#pragma once
#include "Task.h"
#include <string>
#include "Shot.h"
#include "smart_ptr.h"
#include <list>
#include <array>

PTR( Shot );
PTR( Armoury );
PTR( Impact );

class Armoury : public Task {
public:
	static std::string getTag( ) { return "SHOT"; };
	static ArmouryPtr getTask( );
public:
	Armoury( );
	virtual ~Armoury( );
public:
	void add( ShotPtr shot );
	void update( );
	ShotConstPtr getShot( int idx ) const;
	int getMaxShotNum( ) const;
	std::list< ImpactPtr > getImpactList( ) const;
private:
	void updateEnemy( );
	void updateImpact( );
private:
	static const int MAX_SHOT_NUM = 100;
	int _shot_id;
	std::array< ShotPtr, MAX_SHOT_NUM > _shot_list;
	std::list< ImpactPtr > _impacts;
};

