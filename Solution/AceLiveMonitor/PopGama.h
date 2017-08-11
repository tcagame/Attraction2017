#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopGama : public Pop {
public:
	PopGama( const Vector& pos );
	virtual ~PopGama( );
public:
	void update( );
private:
	bool _pop;
	Vector _pos;
};
