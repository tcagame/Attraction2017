#pragma once
#include "smart_ptr.h"
#include "mathmatics.h"
#include "Player.h"

PTR( Shot );

class Shot {
public:
	Shot( const Vector& pos, DIR dir );
	virtual ~Shot( );
public:
	Vector getPos( ) const;
	void update( );
	DIR getDir( ) const;
private:
	Vector _pos;
	DIR _dir;
	Vector _vec;
};

