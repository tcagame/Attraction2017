#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopGhost: public Pop {
public:
	PopGhost( const Vector& pos );
	virtual ~PopGhost( );
public:
	void update( );
private:
	bool _pop;
	Vector _pos;
};

