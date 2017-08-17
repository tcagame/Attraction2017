#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopBat : public Pop {
public:
	PopBat( const Vector& pos );
	virtual ~PopBat( );
protected:
	void create( );
};

