#pragma once
#include "Pop.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Enemy );

class PopSwampZombieA : public Pop {
public:
	PopSwampZombieA( const Vector& pos );
	virtual ~PopSwampZombieA( );
public:
	void update( );
private:
	EnemyWeakPtr _enemy;
};

