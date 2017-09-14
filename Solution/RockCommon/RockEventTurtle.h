#pragma once
#include "RockEventCharacter.h"

class RockEventTurtle : public RockEventCharacter {
public:
	RockEventTurtle( const Vector& pos );
	virtual ~RockEventTurtle( );
protected:
	void act( );
	double getAnimTime( ) const;
};

