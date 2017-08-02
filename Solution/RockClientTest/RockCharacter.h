#pragma once
#include "define.h"
#include "mathmatics.h"

class RockCharacter {
public:
	RockCharacter( const Vector& pos, DOLL id, bool mass = true );
	virtual ~RockCharacter( );
public:
	DOLL getId( ) const;
	void update( );
	Vector getPos( );
protected:
	virtual void act( ) = 0;
	void setVec( const Vector& vec );
	Vector getVec( ) const;
private:
	Vector _pos;
	Vector _vec;
	DOLL _id;
	bool _mass;
};

