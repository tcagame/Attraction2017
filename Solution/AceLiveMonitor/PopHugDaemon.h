#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopHugDaemon : public Pop {
public:
	PopHugDaemon( const Vector& pos );
	virtual ~PopHugDaemon( );
protected:
	void create( );
};

