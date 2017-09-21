#pragma once
#include "Pop.h"
#include "mathmatics.h"

class PopWhiteMist : public Pop {
public:
	PopWhiteMist( const Vector& pos );
	virtual ~PopWhiteMist( );
public:
	void update( );
private:
	int _count;
	int _max_pop_time;
};

