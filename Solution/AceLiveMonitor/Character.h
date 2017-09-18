#pragma once
#include "mathmatics.h"
#include "ace_define.h"
#include "smart_ptr.h"
#include "ViewerDebug.h"

PTR( Character );

class Character {
public:
	Character( const Vector& pos, const int chip_size, const int hp, bool mass = true );
	virtual ~Character( );
public:
	Vector getVec( ) const;
	Vector getPos( ) const;
	void update( );
	virtual void damage( int force );
	bool isOverlapped( CharacterConstPtr target ) const;
	double getOverlappedRadius( ) const;
	AREA getArea( ) const;
	void setArea( AREA area );
	int getChipSize( ) const;
	int getPower( ) const;
	DIR getDir( ) const;
	ViewerDebug::Data::Circle getDebugDataCircle( ) const;
	Vector getOverlappedPos( ) const;
	void shiftPos( );
protected:
	void setDir( DIR dir );
	void setVec( const Vector& vec );
	void setPos( const Vector& pos );
	void setPower( int power );
	bool isStanding( ) const;
	virtual void act( ) = 0;
	int getActCount( ) const;
	void setOverlappedRadius( int radius );
	void setActCount( int count );
private:
	void updateDir( );
	void updateMass( );
private:
	Vector _pos;
	Vector _vec;
	int _chip_size;
	int _power;
	int _act_count;
	bool _mass;
	bool _standing;
	double _radius;
	DIR _dir;
	AREA _area;
};

