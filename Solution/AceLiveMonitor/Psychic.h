#pragma once
#include "smart_ptr.h"
#include "mathmatics.h"
#include "Player.h"

PTR( Psychic );

class Psychic {
public:
	Psychic( const Vector& pos, Player::DIR dir );
	virtual ~Psychic( );
public:
	Vector getPos( ) const;
	void update( );
	int getDir( );
private:
	Vector _pos;
	int _dir;
};

