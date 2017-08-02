#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopLancer : public Pop {
public:
	PopLancer( const Vector& pos );
	virtual ~PopLancer( );
public:
	void update( );
private:
	bool _pop;
	Vector _pos;
};

