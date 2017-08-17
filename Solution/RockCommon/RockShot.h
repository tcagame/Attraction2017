#pragma once
#include "RockCharacter.h"

class RockShot : public RockCharacter {
public:
	RockShot( const int id_, const Vector& pos, const Vector& dir );
	virtual ~RockShot( );
public:
	double getAnimTime( ) const;
	bool isfinished( ) const;
protected:
	void act( );
private:
	void actOutRange( );
private:
	int _id;
	double _size = 1.0;
	bool _out_range;
	bool _finished;
	Vector _rotate = Vector( 0, 0, 0 );
};

