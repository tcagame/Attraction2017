#pragma once
#include "RockCharacter.h"
#include "define.h"

class RockEnemy:  public RockCharacter {
public:
	RockEnemy( const Vector& pos, DOLL id, int force = 1, int radius = 10, int height = 30, bool mass = true, bool head = true );
	virtual ~RockEnemy( );
public:
	int getForce( ) const;
private:
	int _force;
};

