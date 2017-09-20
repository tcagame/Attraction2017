#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopTree : public Pop {
public:
	PopTree( const Vector& pos );
	virtual ~PopTree( );
public:
	void update( );
private:
	bool _pop;
};

