#pragma once
#include "RockMap.h"
#include "mathmatics.h"

class RockMapEntry :	public RockMap {
public:
	RockMapEntry( );
	virtual ~RockMapEntry( );
public:
	void update( );
private:
	bool isNext( const Vector& pos ) const;
};

