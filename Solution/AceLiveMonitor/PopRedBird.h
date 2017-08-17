#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopRedBird : public Pop {
public:
	PopRedBird( const Vector& pos );
	virtual ~PopRedBird( );
protected:
	void create( );
};

