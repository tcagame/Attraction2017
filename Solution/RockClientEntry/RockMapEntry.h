#pragma once
#include "RockMap.h"
#include "mathmatics.h"

PTR( Status );

class RockMapEntry :	public RockMap {
public:
	RockMapEntry( StatusPtr status );
	virtual ~RockMapEntry( );
public:
	void initialize( );
	void update( );
private:
	bool isNext( const Vector& pos ) const;
private:
	StatusPtr _status;
};

