#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopStoneFace : public Pop {
public:
	PopStoneFace( const Vector& pos );
	virtual ~PopStoneFace( );
public:
	void update( );
private:
	int _count;
};

