#pragma once
#include "mathmatics.h"
#include "ace_define.h"
#include "smart_ptr.h"

PTR( Character );

class Character {
public:
	Character( const Vector& pos, int chip_size, bool mass = true );
	virtual ~Character( );
public:
	Vector getVec( ) const;
	Vector getPos( ) const;
	void update( );
	virtual void damage( int force );
	virtual Chip getChip( ) const = 0;
	bool isOverlapped( CharacterConstPtr target ) const;
	double getRadius( ) const;
	bool isFinished( ) const;
protected:
	void setDir( DIR dir );
	DIR getDir( ) const;
	void setVec( const Vector& vec );
	void setPos( const Vector& pos );
	bool isStanding( ) const;
	virtual void act( ) = 0;
	int getActCount( ) const;
	int getChipSize( ) const;
	void setRadius( int radius );
	void setFinished( );
private:
	void updateDir( );
private:
	Vector _pos;
	Vector _vec;
	DIR _dir;
	bool _standing;
	int _chip_size;
	int _act_count;
	double _radius;
	bool _mass;
	bool _finished;
};

