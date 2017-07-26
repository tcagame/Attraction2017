#pragma once
#include "Character.h"
class Enemy : public Character {
public:
	Enemy( const Vector& pos, const int width, bool mass = true );
	virtual ~Enemy( );
protected:
	virtual void act( ) = 0;
};

