#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopGreenZombie : public Pop {
public:
	PopGreenZombie( const Vector& pos );
	virtual ~PopGreenZombie( );
public:
	void update( );
private:
	bool _pop;
	Vector _pos;
};

