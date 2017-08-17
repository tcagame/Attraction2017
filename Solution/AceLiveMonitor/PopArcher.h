#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopArcher : public Pop {
public:
	PopArcher( const Vector& pos );
	virtual ~PopArcher( );
protected:
	void create( );
};

