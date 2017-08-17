#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopSwampZombieA : public Pop {
public:
	PopSwampZombieA( const Vector& pos );
	virtual ~PopSwampZombieA( );
protected:
	void create( );
};

