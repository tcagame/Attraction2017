#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopEyeDemon : public Pop {
public:
	PopEyeDemon( const Vector& pos );
	virtual ~PopEyeDemon( );
public:
	void update( );
private:
	bool _pop;
	Vector _pos;
};

