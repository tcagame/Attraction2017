#pragma once
#include "Pop.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Enemy );

class PopLancer : public Pop {
public:
	PopLancer( const Vector& pos );
	virtual ~PopLancer( );
public:
	void update( );
private:
	int _count;
	EnemyWeakPtr _enemy;
};

