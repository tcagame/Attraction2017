#pragma once
#include "RockShot.h"
class RockShotAncestors : public RockShot {
public:
	RockShotAncestors( const int id, const Vector& pos, const Vector& dir, const int power );
	virtual ~RockShotAncestors( );
protected:
	void act( );
private:
	int _target_id;
};

