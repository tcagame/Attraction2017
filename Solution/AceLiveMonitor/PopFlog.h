#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopFlog : public Pop {
public:
	PopFlog( const Vector& pos );
	virtual ~PopFlog( );
protected:
	void create( );
};

