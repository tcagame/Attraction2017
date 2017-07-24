#pragma once
#include "Character.h"
class Enemy : public Character {
public:
	Enemy( const Vector& pos, const int width );
	virtual ~Enemy( );
};

