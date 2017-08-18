#pragma once
#include "RockCharacter.h"
#include "define.h"

class RockEnemy:  public RockCharacter {
public:
	RockEnemy( const Vector& pos, DOLL id, int hp, int force = 1, int radius = 10, int height = 30, bool mass = true, bool head = true );
	virtual ~RockEnemy( );
public:
	int getForce( ) const;
	void damage( int force );
	bool isFinished( ) const;
private:
	int _force;
	int _hp;
	bool _finished;
};

