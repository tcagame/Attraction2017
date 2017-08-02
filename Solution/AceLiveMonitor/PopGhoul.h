#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopGhoul : public Pop {
public:
	PopGhoul( const Vector& pos );
	virtual ~PopGhoul( );
public:
	void update( );
private:
	bool _pop;
	Vector _pos;
};

