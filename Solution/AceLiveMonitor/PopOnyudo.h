#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopOnyudo : public Pop {
public:
	PopOnyudo( const Vector& pos );
	virtual ~PopOnyudo( );
public:
	void update( );
private:
	bool _pop;
	Vector _pos;
};

