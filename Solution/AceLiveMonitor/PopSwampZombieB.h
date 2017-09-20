#pragma once
#include "Pop.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Enemy );

class PopSwampZombieB : public Pop {
public:
	PopSwampZombieB( const Vector& pos );
	virtual ~PopSwampZombieB( );
public:
	void update( );
private:
	EnemyWeakPtr _enemy;
};

