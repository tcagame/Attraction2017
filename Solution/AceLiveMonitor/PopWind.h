#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopWind : public Pop {
public:
	PopWind( const Vector& pos );
	virtual ~PopWind( );
protected:
	void create( );
};

