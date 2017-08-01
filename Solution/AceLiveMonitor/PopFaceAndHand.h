#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopFaceAndHand : public Pop {
public:
	PopFaceAndHand( Vector pos );
	virtual ~PopFaceAndHand( );
public:
	void update( );
private:
	Vector _pos;
	bool _pop;
};

