#pragma once
#include "RockEventCharacter.h"
class RockEventOtohime : public RockEventCharacter {
public:
	RockEventOtohime( const Vector& pos );
	virtual ~RockEventOtohime( );
protected:
	void act( ) { };
	double getAnimTime( ) const { return 0; };
};

