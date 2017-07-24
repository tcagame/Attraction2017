#pragma once
#include "smart_ptr.h"
#include "ace_define.h"
#include <array>

PTR( Player );

class Family {
public:
	Family( );
	virtual ~Family( );
public:
	void update( );
	PlayerConstPtr getPlayer( int player_id ) const;
	PlayerPtr getPlayer( int player_id );
private:
	std::array< PlayerPtr, ACE_PLAYER_NUM > _player;
};

