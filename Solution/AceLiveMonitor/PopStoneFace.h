#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopStoneFace : public Pop {
public:
	PopStoneFace( const Vector& pos );
	virtual ~PopStoneFace( );
protected:
	void create( );
};

