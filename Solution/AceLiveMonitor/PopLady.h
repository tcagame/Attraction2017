#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopLady : public Pop {
public:
	PopLady( const Vector& pos );
	virtual ~PopLady( );
protected:
	void create( );
};

