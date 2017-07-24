#pragma once
#include "Task.h"
#include <string>
#include "Shot.h"
#include "Player.h"
#include "Shot.h"
#include "smart_ptr.h"
#include <vector>

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
	void shot( Vector pos, Player::DIR dir );
	void update( );
	ShotPtr getShot( int index ) const;
	int getShotNum( ) const;
private:
	std::vector< ShotPtr> _shot_list;
};

