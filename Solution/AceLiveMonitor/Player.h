#pragma once
#include "mathmatics.h"

class Player {
public:
	Player( Vector pos );
	virtual ~Player( );
public:
	void update( );
	Vector getPos( ) const;
private:
	Vector _pos;
	Vector _vec;
};

