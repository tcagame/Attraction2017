#pragma once
#include "Character.h"
class Enemy : public Character {
public:
	Enemy( const Vector& pos, const int chip_size, const int hp, bool mass = true );
	virtual ~Enemy( );
public:
	bool isInScreen( ) const;
protected:
	virtual void act( ) = 0;
};

