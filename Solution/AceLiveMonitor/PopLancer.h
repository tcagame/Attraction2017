#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopLancer : public Pop {
public:
	PopLancer( const Vector& pos );
	virtual ~PopLancer( );
protected:
	void create( );
};

