#pragma once
#include "RockCharacter.h"
class RockCasket : public RockCharacter {
public:
	RockCasket( const Vector& pos );
	virtual ~RockCasket( );
public:
	void act( );
	ModelMV1Ptr getModel( ) const;
};

