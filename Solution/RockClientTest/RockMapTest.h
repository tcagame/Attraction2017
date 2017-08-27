#pragma once
#include "RockMap.h"
#include "mathmatics.h"

PTR( Movie );

class RockMapTest :	public RockMap {
public:
	RockMapTest( );
	virtual ~RockMapTest( );
public:
	void update( );
private:
	bool isNext( const Vector& pos ) const;
	MoviePtr _movie;
};

