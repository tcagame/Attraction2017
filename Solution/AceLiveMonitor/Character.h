#pragma once
#include "mathmatics.h"
#include "ace_define.h"

class Character {
public:
	Character( const Vector& pos, int chip_size, bool mass = true );
	virtual ~Character( );
public:
	Vector getVec( ) const;
	Vector getPos( ) const;
	void update( );
	virtual Chip getChip( ) const = 0;
protected:
	void setDir( DIR dir );
	DIR getDir( ) const;
	void setVec( const Vector& vec );
	void setPos( const Vector& pos );
	bool isStanding( ) const;
	virtual void act( ) = 0;
	int getActCount( ) const;
	int getChipSize( ) const;
private:
	void updateDir( );
private:
	Vector _pos;
	Vector _vec;
	DIR _dir;
	bool _standing;
	int _chip_size;
	int _act_count;
	bool _mass;
};

