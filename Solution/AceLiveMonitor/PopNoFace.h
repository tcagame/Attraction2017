#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopNoFace : public Pop {
public:
	PopNoFace( const Vector& pos );
	virtual ~PopNoFace( );
protected:
	void create( );
};

