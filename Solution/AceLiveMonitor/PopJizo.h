#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopJizo : public Pop {
public:
	PopJizo( const Vector& pos );
	virtual ~PopJizo( );
protected:
	void create( );
};

