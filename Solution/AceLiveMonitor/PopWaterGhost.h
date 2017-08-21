#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopWaterGhost : public Pop {
public:
	PopWaterGhost( const Vector& pos );
	virtual ~PopWaterGhost( );
protected:
	void create( );
};

