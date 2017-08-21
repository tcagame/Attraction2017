#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopShell : public Pop {
public:
	PopShell( const Vector& pos );
	virtual ~PopShell( );
protected:
	void create( );
};

