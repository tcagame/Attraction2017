#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopSwampZombieB : public Pop {
public:
	PopSwampZombieB( const Vector& pos );
	virtual ~PopSwampZombieB( );
public:
	void update( );
private:
	bool _pop;
	Vector _pos;
};

