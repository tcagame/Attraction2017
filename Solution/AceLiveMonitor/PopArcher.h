#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopArcher : public Pop {
public:
	PopArcher( const Vector& pos );
	virtual ~PopArcher( );
public:
	void update( );
private:
	bool _pop;
	Vector _pos;
};

