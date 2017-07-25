#pragma once
#include "Task.h"
#include <string>
#include "Shot.h"
#include "Player.h"
#include "Shot.h"
#include "smart_ptr.h"
#include <array>

PTR( Shot );
PTR( Armoury );

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
public:
	static const int MAX_SHOT_NUM = 100;
private:
	std::array< ShotPtr, MAX_SHOT_NUM > _shot_list;
};

