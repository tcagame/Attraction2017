#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopGrayMist : public Pop {
public:
	PopGrayMist( const Vector& pos );
	virtual ~PopGrayMist( );
protected:
	void create( );
};

