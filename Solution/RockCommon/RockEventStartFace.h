#pragma once
#include "RockEventCharacter.h"

class RockEventStartFace : public RockEventCharacter {
public:
	RockEventStartFace( const Vector pos );
	virtual ~RockEventStartFace( );
protected:
	void act( );
	double getAnimTime( ) const;
};

