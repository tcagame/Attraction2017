#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopFaceAndHand : public Pop {
public:
	PopFaceAndHand( const Vector& pos );
	virtual ~PopFaceAndHand( );
public:
	void update( );
private:
	int _max_pop_time;
	int _count;
};

