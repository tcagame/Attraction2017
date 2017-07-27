#pragma once
#include "smart_ptr.h"
#include "Character.h"

class Shot : public Character {
public:
	Shot( const Vector& pos, DIR dir, int power );
	virtual ~Shot( );
public:
	void update( );
	DIR getDir( ) const;
	int getPower( ) const;
	bool isFinish( ) const;
	Chip getChip( ) const;
protected:
	void act( );
private:
	int _power;
	Vector _pos;
	DIR _dir;
};

