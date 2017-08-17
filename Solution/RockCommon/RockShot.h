#pragma once
#include "RockCharacter.h"

class RockShot : public RockCharacter {
public:
	RockShot( const int id_, const Vector& pos, const Vector& dir );
	virtual ~RockShot( );
public:
	double getAnimTime( ) const;
	bool isBack( ) const;
	bool isFinished( ) const;
	void setBack( );
	void setFinished( );
protected:
	void act( );
private:
	void actOutBack( );
private:
	int _id;
	double _size = 1.0;
	bool _back;
	bool _finished;
	Vector _rotate = Vector( 0, 0, 0 );
};

