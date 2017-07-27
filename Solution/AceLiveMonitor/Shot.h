#pragma once
#include "smart_ptr.h"
#include "mathmatics.h"
#include "Player.h"

PTR( Shot );

class Shot {
public:
	Shot( const Vector& pos, DIR dir, int power );
	virtual ~Shot( );
public:
	Vector getPos( ) const;
	void update( );
	DIR getDir( ) const;
	int getPower( ) const;
	int getCount( ) const;
	bool isFinish( ) const;
private:
	int _power;
	int _count;
	Vector _pos;
	DIR _dir;
	Vector _vec;
};

