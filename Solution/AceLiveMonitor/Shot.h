#pragma once
#include "smart_ptr.h"
#include "Character.h"

class Shot : public Character {
public:
	Shot( const Vector& pos, int power );
	virtual ~Shot( );
public:
	int getPower( ) const;
	virtual void setSynchronousData( unsigned char type, int camera_pos ) const = 0;
	virtual void erase( );
protected:
	void setPower( int power );
	Vector getOriginPos( ) const;
private:
	int _power;
	Vector _pos;
	Vector _origin_pos;
};

