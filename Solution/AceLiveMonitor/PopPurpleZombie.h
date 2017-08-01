#pragma once
#include "mathmatics.h"
#include "Pop.h"

class PopPurpleZombie : public Pop {
public:
	PopPurpleZombie( Vector pos );
	virtual ~PopPurpleZombie( );
public:
	void update( );
private:
	bool _pop;
	Vector _pos;
};

