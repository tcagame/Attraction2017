#pragma once
#include "mathmatics.h"

class RockImpact {
public:
	RockImpact( const Vector& pos, double size = 1.0 );
	virtual ~RockImpact( );
public:
	void update( );
	bool isFinished( ) const;
	double getSize( ) const;
	Vector getPos( ) const;
private:
	int _count;
	double _size;
	bool _finished;
	Vector _pos;
};

