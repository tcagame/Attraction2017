#pragma once
#include "Pop.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Enemy );

class PopShishimai : public Pop {
public:
	PopShishimai( const Vector& pos );
	virtual ~PopShishimai( );
public:
	void update( );
private:
	int _count;
	EnemyWeakPtr _enemy;
};

