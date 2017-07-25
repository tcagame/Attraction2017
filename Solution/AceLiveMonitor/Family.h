#pragma once
#include "Task.h"
#include <string>
#include "smart_ptr.h"
#include "ace_define.h"
#include <array>

PTR( Family );
PTR( Player );

class Family : public Task {
public:
	static std::string getTag( ) { return "FAMILY"; };
	static FamilyPtr getTask( );
public:
	Family( );
	virtual ~Family( );
public:
	void initialize( );
	void update( );
	PlayerConstPtr getPlayer( int player_id ) const;
	PlayerPtr getPlayer( int player_id );
	double getPlayersPosX( ) const;
private:
	std::array< PlayerPtr, ACE_PLAYER_NUM > _player;
};

