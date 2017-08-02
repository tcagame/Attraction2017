#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopNoNeckGhost : public Pop {
public:
	PopNoNeckGhost( const Vector& pos );
	virtual ~PopNoNeckGhost( );
public:
	void update( );
private:
	bool _pop;
	Vector _pos;
};

