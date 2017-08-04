#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopLady : public Pop {
public:
	PopLady( const Vector& pos );
	virtual ~PopLady( );
public:
	void update( );
private:
	bool _pop;
	Vector _pos;
};

