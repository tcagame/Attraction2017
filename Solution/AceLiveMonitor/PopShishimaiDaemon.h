#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopShishimaiDaemon : public Pop {
public:
	PopShishimaiDaemon( const Vector& pos );
	virtual ~PopShishimaiDaemon( );
protected:
	void create( );
};

