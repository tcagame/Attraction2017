#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopStone : public Pop {
public:
	PopStone( const Vector& pos );
	virtual ~PopStone( );
protected:
	void create( );
};

