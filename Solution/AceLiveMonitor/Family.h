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
	PlayerPtr getPlayer( int player_id ) const;
private:
	std::array< PlayerPtr, ACE_PLAYER_NUM > _player;
};

