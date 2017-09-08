#pragma once
#include "RockMap.h"
#include "mathmatics.h"

class RockMapEntry :	public RockMap {
public:
	RockMapEntry( );
	virtual ~RockMapEntry( );
public:
	void initialize( );
	void update( );
private:
	bool isNext( const Vector& pos ) const;
};

