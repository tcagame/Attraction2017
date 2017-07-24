#pragma once
#include "mathmatics.h"
class Character {
public:
	enum DIR {
		DIR_LEFT,
		DIR_RIGHT,
	};
public:
	Character( const Vector& pos, int chip_size );
	virtual ~Character( );
public:
	Vector getVec( ) const;
	Vector getPos( ) const;
	DIR getDir( ) const;
	void update( );
	virtual void getChipIndex( int* cx, int* cy ) const;
protected:
	void setVec( const Vector& vec );
	void setPos( const Vector& pos );
	bool isStanding( ) const;
	virtual void act( ) = 0;
	int getActCount( ) const;
private:
	void updateDir( );
private:
	Vector _pos;
	Vector _vec;
	DIR _dir;
	bool _standing;
	int _chip_size;
	int _act_count;
};

