#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopBlueMonk : public Pop {
public:
	PopBlueMonk( const Vector& pos );
	virtual ~PopBlueMonk( );
protected:
	void create( );
};

