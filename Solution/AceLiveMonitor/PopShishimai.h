#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopShishimai : public Pop {
public:
	PopShishimai( const Vector& pos );
	virtual ~PopShishimai( );
public:
	void update( );
private:
	bool _pop;
	Vector _pos;
};

