#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopNoNeckGhost : public Pop {
public:
	PopNoNeckGhost( const Vector& pos );
	virtual ~PopNoNeckGhost( );
protected:
	void create( );
};

