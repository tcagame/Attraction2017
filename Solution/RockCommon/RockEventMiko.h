#pragma once
#include "RockEventCharacter.h"
class RockEventMiko : public RockEventCharacter {
public:
	RockEventMiko( const Vector& pos );
	virtual ~RockEventMiko( );
protected:
	void act( );
	double getAnimTime( ) const { return 0; };
};

