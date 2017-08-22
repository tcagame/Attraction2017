#pragma once
#include "RockMap.h"
#include "mathmatics.h"

class RockMapTest :	public RockMap {
public:
	RockMapTest( );
	virtual ~RockMapTest( );
public:
	void update( );
private:
	bool isNext( const Vector& pos ) const;
};

