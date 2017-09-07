#pragma once
#include "RockCharacter.h"

class RockEventCharacter : public RockCharacter {
public:
	RockEventCharacter( const Vector& pos, DOLL doll, int radius, int height, bool mass );
	virtual ~RockEventCharacter( );
public:
	void damage( int force );
	ModelMV1Ptr getModel( ) const;
private:
	virtual double getAnimTime( ) const;
};

