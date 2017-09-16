#pragma once
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( ModelMV1 );

class RockAlter {
public:
	RockAlter( const Vector& pos, const Vector& dir );
	virtual ~RockAlter( );
public:
	bool isInRange( const Vector& pos ) const;
	bool isActive( ) const;
	void setActive( bool active );
	ModelMV1Ptr getModel( ) const;
	Vector getPos( ) const;
public:
	static const int RANGE = 80;
private:
	Vector _pos;
	Vector _dir;
	bool _active;
};

