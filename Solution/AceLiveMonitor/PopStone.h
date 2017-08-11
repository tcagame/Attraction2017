#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopStone : public Pop {
public:
	PopStone( const Vector& pos );
	virtual ~PopStone( );
public:
	void update( );
private:
	bool _pop;
	Vector _pos;
};

