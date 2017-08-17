#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopSwampZombieB : public Pop {
public:
	PopSwampZombieB( const Vector& pos );
	virtual ~PopSwampZombieB( );
protected:
	void create( );
};

