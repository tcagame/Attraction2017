#pragma once
#include "RockEventCharacter.h"

class EventTurtle : public RockEventCharacter {
public:
	EventTurtle( const Vector& pos );
	virtual ~EventTurtle( );
protected:
	void act( );
	double getAnimTime( ) const;
};

