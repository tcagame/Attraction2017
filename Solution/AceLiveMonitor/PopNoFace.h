#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopNoFace : public Pop {
public:
	PopNoFace( Vector pos );
	virtual ~PopNoFace( );
public:
	void update( );
private:
	Vector _pos;
	bool _pop;
};

