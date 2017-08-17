#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopHugDemon : public Pop {
public:
	PopHugDemon( const Vector& pos );
	virtual ~PopHugDemon( );
protected:
	void create( );
};

