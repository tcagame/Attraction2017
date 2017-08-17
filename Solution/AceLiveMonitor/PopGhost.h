#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopGhost: public Pop {
public:
	PopGhost( const Vector& pos );
	virtual ~PopGhost( );
protected:
	void create( );
};

