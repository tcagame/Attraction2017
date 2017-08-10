#pragma once
#include "define.h"
#include "mathmatics.h"

class RockCharacter {
public:
	RockCharacter( const Vector& pos, DOLL id, bool mass = true );
	virtual ~RockCharacter( );
public:
	DOLL getDoll( ) const;
	void update( );
	Vector getPos( );
	virtual double getAnimTime( ) const = 0;
	bool isOverRapped( ) const;
protected:
	virtual void act( ) = 0;
	void setVec( const Vector& vec );
	Vector getVec( ) const;
	void setDoll( DOLL doll );
	bool isStanding( ) const;
	void setActCount( int count );
	int getActCount( ) const;
	void setRadius( int radius );
	int getRadius( ) const;
private:
	void collision( );
private:
	Vector _pos;
	Vector _vec;
	DOLL _doll;
	bool _mass;
	bool _standing;
	int _radius;
	int _act_count;
};

