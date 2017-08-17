#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopGreenZombie : public Pop {
public:
	PopGreenZombie( const Vector& pos );
	virtual ~PopGreenZombie( );
protected:
	void create( );
};

