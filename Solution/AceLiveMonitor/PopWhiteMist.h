#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopWhiteMist : public Pop {
public:
	PopWhiteMist( const Vector& pos );
	virtual ~PopWhiteMist( );
protected:
	void create( );
};

