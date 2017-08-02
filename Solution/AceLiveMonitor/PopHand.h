#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopHand : public Pop {
public:
	PopHand( const Vector& pos );
	virtual ~PopHand( );
public:
	void update( );
private:
	bool _pop;
	Vector _pos;
};

