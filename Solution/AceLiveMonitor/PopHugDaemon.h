#pragma once
#include "Pop.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Enemy );

class PopHugDaemon : public Pop {
public:
	PopHugDaemon( const Vector& pos );
	virtual ~PopHugDaemon( );
public:
	void update( );
private:
	int _count;
	EnemyWeakPtr _enemy;
};

