#pragma once
#include "RockShot.h"
class RockShotPlayer : public RockShot {
public:
	RockShotPlayer( const int id, const Vector& pos, const Vector& dir, const int power );
	virtual ~RockShotPlayer( );
public:
	void setBack( );
protected:
	void act( );
private:
	void actOutBack( );
private:
	bool _back;
};

