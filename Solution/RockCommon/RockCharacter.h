#pragma once
#include "define.h"
#include "mathmatics.h"
#include "smart_ptr.h"
#include "ModelMV1.h"

PTR( RockCharacter );

class RockCharacter {
public:
	RockCharacter( const Vector& pos, DOLL doll, int radius, int height, bool mass = true, bool head = true, bool col = true );
	virtual ~RockCharacter( );
public:
	void update( );
	Vector getPos( ) const;
	Vector getDir( ) const;
	int getRadius( ) const;
	int getHeight( ) const;
	virtual void damage( int force );
	bool isHead( ) const;
	bool isOnHead( RockCharacterConstPtr target ) const;
	bool isOverLapped( RockCharacterConstPtr target ) const;
	void back( );
	virtual void bound( );
	virtual ModelMV1Ptr getModel( ) const { return ModelMV1Ptr( ); };
protected:
	virtual void act( ) = 0;
	void setVec( const Vector& vec );
	void setPos( const Vector& pos );
	Vector getVec( ) const;
	bool isStanding( ) const;
	void setActCount( int count );
	int getActCount( ) const;
	void setRadius( int radius );
	DOLL getDoll( ) const;
	void setDoll( DOLL doll );
	void setMass( bool mass );
	void setCol( bool col );
	bool isOnMapModel( ) const;
private:
	Vector _pos;
	Vector _vec;
	Vector _dir;
	DOLL _doll;
	bool _mass;
	bool _standing;
	int _radius;
	int _height;
	int _act_count;
	bool _head;
	bool _col;
};

