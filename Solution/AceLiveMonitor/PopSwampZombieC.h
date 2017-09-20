#pragma once
#include "Pop.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Enemy );

class PopSwampZombieC : public Pop {
public:
	PopSwampZombieC( const Vector& pos );
	virtual ~PopSwampZombieC( );
public:
	void update( );
private:
	EnemyWeakPtr _enemy;
};

