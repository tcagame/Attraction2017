#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopGrayMist : public Pop {
public:
	PopGrayMist( const Vector& pos );
	virtual ~PopGrayMist( );
public:
	void update( );
private:
	int _count;
	int _max_pop_time;
};

