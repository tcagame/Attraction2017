#pragma once
#include "RockEventCharacter.h"
#include "Status.h"

PTR( Status );

class RockEventMiko : public RockEventCharacter {
public:
	RockEventMiko( const Vector& pos );
	virtual ~RockEventMiko( );
protected:
	void act( );
	double getAnimTime( ) const { return 0; };
private:
	StatusPtr _status;
};

