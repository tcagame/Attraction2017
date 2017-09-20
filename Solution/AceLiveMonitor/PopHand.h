#pragma once
#include "Pop.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Enemy );

class PopHand : public Pop {
public:
	PopHand( const Vector& pos );
	virtual ~PopHand( );
public:
	void update( );
private:
	int _count;
	EnemyWeakPtr _enemy;
};

