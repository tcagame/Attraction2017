#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopSkeleton : public Pop {
public:
	PopSkeleton( const Vector& pos );
	virtual ~PopSkeleton( );
public:
	void update( );
private:
	bool _pop;
	Vector _pos;
};

