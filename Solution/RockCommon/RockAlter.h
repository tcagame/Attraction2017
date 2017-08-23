#pragma once
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( ModelMV1 );

class RockAlter {
public:
	RockAlter( const Vector& pos );
	virtual ~RockAlter( );
public:
	bool isInRange( const Vector& pos ) const;
	bool isActive( ) const;
	void setActive( bool active );
	ModelMV1Ptr getModel( ) const;
private:
	Vector _pos;
	bool _active;
};

