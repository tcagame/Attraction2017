#pragma once
#include "RockMap.h"
#include "mathmatics.h"

PTR( Movie );

class RockMapResult :	public RockMap {
public:
	RockMapResult( );
	virtual ~RockMapResult( );
public:
	void initialize( );
	void update( );
private:
	bool _darw_butta;
};

