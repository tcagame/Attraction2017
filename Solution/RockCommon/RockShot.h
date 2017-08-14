#pragma once
#include "RockCharacter.h"

class RockShot : public RockCharacter {
public:
	RockShot( const Vector& pos );
	virtual ~RockShot( );
public:
	int getEffectHandle( ) const;
	double getAnimTime( ) const;
protected:
	void act( );
private:
	int _handle;
	double _size = 1.0;
	Vector _rotate = Vector( 0, 0, 0 );
};

