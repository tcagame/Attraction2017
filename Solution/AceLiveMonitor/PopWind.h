#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopWind : public Pop {
public:
	PopWind( const Vector& pos );
	virtual ~PopWind( );
public:
	void update( );
private:
	bool _pop;
	Vector _pos;
};

