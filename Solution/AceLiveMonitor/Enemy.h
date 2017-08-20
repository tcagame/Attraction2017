#pragma once
#include "Character.h"
class Enemy : public Character {
public:
	Enemy( const Vector& pos, const int chip_size, const int hp, bool mass = true );
	virtual ~Enemy( );
public:
	bool isInScreen( ) const;
	int getForce( ) const;
protected:
	virtual void act( ) = 0;
	void setForce( int force );
private:
	int _force;
};

