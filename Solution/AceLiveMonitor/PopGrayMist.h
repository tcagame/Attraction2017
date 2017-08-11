#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopGrayMist : public Pop {
public:
	PopGrayMist( const Vector& pos );
	virtual ~PopGrayMist( );
public:
	void update( );
private:
	bool _pop;
	Vector _pos;
};

