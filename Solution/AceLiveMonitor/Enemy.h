#pragma once
#include "Character.h"
class Enemy : public Character {
public:
	Enemy( const Vector& pos, const int chip_size, const int hp, bool mass = true );
	virtual ~Enemy( );
public:
	virtual void setSynchronousData( int camera_pos ) const = 0;
	bool isInScreen( ) const;
	int getForce( ) const;
protected:
	virtual void act( ) = 0;
	void setForce( int force );
	unsigned char getType( ) const;
private:
	int _force;
};

