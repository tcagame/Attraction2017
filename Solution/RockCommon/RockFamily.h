#pragma once
#include "Task.h"
#include <string>
#include <array>
#include "define.h"
#include "Status.h"
#include "mathmatics.h"

PTR( RockFamily );
PTR( RockPlayer );
PTR( Status );

class RockFamily : public Task {
public:
	static std::string getTag( ) { return "ROCKFAMILY"; };
	static RockFamilyPtr getTask( );
public:
	RockFamily( StatusPtr status );
	virtual ~RockFamily( );
public:
	void initialize( );
	void update( );
	RockPlayerPtr getPlayer( int id ) const;
	Vector getCameraPos( ) const;
private:
	std::array< RockPlayerPtr, ROCK_PLAYER_NUM > _player;
};

