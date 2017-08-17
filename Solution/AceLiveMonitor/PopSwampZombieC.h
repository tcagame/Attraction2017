#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopSwampZombieC : public Pop {
public:
	PopSwampZombieC( const Vector& pos );
	virtual ~PopSwampZombieC( );
protected:
	void create( );
};

