#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopBlueMonk : public Pop {
public:
	PopBlueMonk( const Vector& pos );
	virtual ~PopBlueMonk( );
public:
	void update( );
private:
	bool _pop;
	Vector _pos;
};

