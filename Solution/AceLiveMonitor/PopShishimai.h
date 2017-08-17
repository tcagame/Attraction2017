#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopShishimai : public Pop {
public:
	PopShishimai( const Vector& pos );
	virtual ~PopShishimai( );
protected:
	void create( );
};

