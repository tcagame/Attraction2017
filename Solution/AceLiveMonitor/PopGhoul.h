#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopGhoul : public Pop {
public:
	PopGhoul( const Vector& pos );
	virtual ~PopGhoul( );
protected:
	void create( );
};

