#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopJizo : public Pop {
public:
	PopJizo( const Vector& pos );
	virtual ~PopJizo( );
public:
	void update( );
private:
	bool _pop;
	Vector _pos;
};

