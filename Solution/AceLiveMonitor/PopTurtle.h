#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopTurtle : public Pop {
public:
	PopTurtle( const Vector& pos );
	virtual ~PopTurtle( );
protected:
	void create( );
};

