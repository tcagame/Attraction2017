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
	virtual void setSynchronousData( unsigned char type, int camera_pos ) const = 0;
protected:
	void setPower( int power );
	Vector getOriginPos( ) const;
private:
	int _power;
	Vector _pos;
	Vector _origin_pos;
	DIR _dir;
};

