#pragma once
#include "smart_ptr.h"
#include "mathmatics.h"
#include "Player.h"

PTR( Shot );

class Shot {
public:
	Shot( const Vector& pos, Player::DIR dir );
	virtual ~Shot( );
public:
	Vector getPos( ) const;
	void update( );
	int getDir( ) const;
private:
	Vector _pos;
	int _dir;
};

