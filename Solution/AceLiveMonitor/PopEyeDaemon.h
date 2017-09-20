#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopEyeDaemon : public Pop {
public:
	PopEyeDaemon( const Vector& pos );
	virtual ~PopEyeDaemon( );
public:
	void update( );
private:
	int _count;
};

