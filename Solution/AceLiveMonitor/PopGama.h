#pragma once
#include "Pop.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Enemy );

class PopGama : public Pop {
public:
	PopGama( const Vector& pos );
	virtual ~PopGama( );
public:
	void update( );
private:
	EnemyWeakPtr _enemy;
	int _count;
};
