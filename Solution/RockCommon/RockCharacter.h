#pragma once
#include "define.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( RockCharacter );

class RockCharacter {
public:
	RockCharacter( const Vector& pos, DOLL id, int radius, int height, bool mass = true, bool head = true );
	virtual ~RockCharacter( );
public:
	DOLL getDoll( ) const;
	void update( );
	Vector getPos( ) const;
	int getRadius( ) const;
	int getHeight( ) const;
	virtual double getAnimTime( ) const = 0;
	virtual void damage( int force );
	bool isHead( ) const;
	bool isOnHead( RockCharacterConstPtr target ) const;
	bool isOverRapped( RockCharacterConstPtr target ) const;
	void back( );
	virtual void bound( );
protected:
	virtual void act( ) = 0;
	void setVec( const Vector& vec );
	void setPos( const Vector& pos );
	Vector getVec( ) const;
	void setDoll( DOLL doll );
	bool isStanding( ) const;
	void setActCount( int count );
	int getActCount( ) const;
	void setRadius( int radius );
private:
	Vector _pos;
	Vector _vec;
	DOLL _doll;
	bool _mass;
	bool _standing;
	int _radius;
	int _height;
	int _act_count;
	bool _head;
};

