#pragma once
#include "Pop.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Enemy );

class PopJizo : public Pop {
public:
	PopJizo( const Vector& pos );
	virtual ~PopJizo( );
public:
	void update( );
private:
	int _count;
	EnemyWeakPtr _enemy;
};

