#pragma once
#include "mathmatics.h"
class Pop {
public:
	Pop( const Vector& pos );
	virtual ~Pop( );
public:
	virtual void update( ) = 0;
protected:
	Vector getPos( ) const;
	bool isInScreen( ) const;
	bool isInRangePlayer( int range ) const;
private:
	Vector _pos;
};

