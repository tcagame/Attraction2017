#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopSwampZombieA : public Pop {
public:
	PopSwampZombieA( const Vector& pos );
	virtual ~PopSwampZombieA( );
public:
	void update( );
private:
	bool _pop;
	Vector _pos;
};

