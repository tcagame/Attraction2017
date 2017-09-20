#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopRedBird : public Pop {
public:
	PopRedBird( const Vector& pos );
	virtual ~PopRedBird( );
public:
	void update( );
private:
	int _count;
};

