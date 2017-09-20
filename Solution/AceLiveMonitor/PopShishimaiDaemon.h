#pragma once
#include "Pop.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Enemy );

class PopShishimaiDaemon : public Pop {
public:
	PopShishimaiDaemon( const Vector& pos );
	virtual ~PopShishimaiDaemon( );
public:
	void update( );
private:
	int _count;
	EnemyWeakPtr _enemy;
};

