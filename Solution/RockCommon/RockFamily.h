#pragma once
#include "Task.h"
#include <string>
#include <array>
#include "define.h"

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
private:
	std::array< RockPlayerPtr, ROCK_PLAYER_NUM > _player;
	StatusPtr _status;
};

