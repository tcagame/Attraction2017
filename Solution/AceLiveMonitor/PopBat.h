#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopBat : public Pop {
public:
	PopBat( const Vector& pos );
	virtual ~PopBat( );
public:
	void update( );
private:
	bool _pop;
	Vector _pos;
};

