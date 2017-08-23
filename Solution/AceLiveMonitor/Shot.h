#pragma once
#include "smart_ptr.h"
#include "Character.h"

class Shot : public Character {
public:
	Shot( const Vector& pos, DIR dir, int power );
	virtual ~Shot( );
public:
	DIR getDir( ) const;
	int getPower( ) const;
	void setSynchronousData( unsigned char type, int camera_pos ) const;
protected:
	void act( );
private:
	int _power;
	Vector _pos;
	DIR _dir;
};

