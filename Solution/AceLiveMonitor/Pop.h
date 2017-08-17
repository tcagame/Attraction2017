#pragma once
#include "mathmatics.h"
class Pop {
public:
	Pop( const Vector& pos );
	virtual ~Pop( );
public:
	void update( );
protected:
	virtual void create( ) = 0;
	Vector getPos( ) const;
private:
	bool isInScreen( ) const;
private:
	Vector _pos;
	int _count;
};

