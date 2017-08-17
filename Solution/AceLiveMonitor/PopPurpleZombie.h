#pragma once
#include "mathmatics.h"
#include "Pop.h"

class PopPurpleZombie : public Pop {
public:
	PopPurpleZombie( const Vector& pos );
	virtual ~PopPurpleZombie( );
protected:
	void create( );
};

