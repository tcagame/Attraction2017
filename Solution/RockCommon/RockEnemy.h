#pragma once
#include "RockCharacter.h"
#include "define.h"
#include "smart_ptr.h"

PTR( RockPlayer );

class RockEnemy:  public RockCharacter {
public:
	RockEnemy( const Vector& pos, DOLL id, int force = 1, bool mass = true, bool head = false );
	virtual ~RockEnemy( );
public:
	int getForce( ) const;
	bool isHead( ) const;
	bool isOverRapped( RockPlayerConstPtr target ) const;
private:
	int _force;
	bool _head;
};

