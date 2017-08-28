#pragma once
#include "RockMap.h"
#include "mathmatics.h"

PTR( Movie );

class RockMapResult :	public RockMap {
public:
	RockMapResult( );
	virtual ~RockMapResult( );
public:
	void update( );
};

