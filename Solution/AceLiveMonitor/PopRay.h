#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopRay : public Pop {
public:
	PopRay( const Vector& pos );
	virtual ~PopRay( );
protected:
	void create( );
};

