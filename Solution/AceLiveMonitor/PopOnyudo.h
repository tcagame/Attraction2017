#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopOnyudo : public Pop {
public:
	PopOnyudo( const Vector& pos );
	virtual ~PopOnyudo( );
protected:
	void create( );
};

