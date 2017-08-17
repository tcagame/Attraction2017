#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopMoth : public Pop {
public:
	PopMoth( const Vector& pos );
	virtual ~PopMoth( );
protected:
	void create( );
};

