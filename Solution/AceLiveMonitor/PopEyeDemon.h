#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopEyeDemon : public Pop {
public:
	PopEyeDemon( const Vector& pos );
	virtual ~PopEyeDemon( );
protected:
	void create( );
};

