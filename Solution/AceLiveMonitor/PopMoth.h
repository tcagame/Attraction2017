#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopMoth : public Pop {
public:
	PopMoth( const Vector& pos );
	virtual ~PopMoth( );
public:
	void update( );
private:
	bool _pop;
	Vector _pos;
};

