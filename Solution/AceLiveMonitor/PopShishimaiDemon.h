#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopShishimaiDemon : public Pop {
public:
	PopShishimaiDemon( const Vector& pos );
	virtual ~PopShishimaiDemon( );
public:
	void update( );
private:
	bool _pop;
	Vector _pos;
};

