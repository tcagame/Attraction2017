#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopHugDemon : public Pop {
public:
	PopHugDemon( const Vector& pos );
	virtual ~PopHugDemon( );
public:
	void update( );
private:
	bool _pop;
	Vector _pos;
};

