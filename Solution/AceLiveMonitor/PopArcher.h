#pragma once
#include "Pop.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Enemy );

class PopArcher : public Pop {
public:
	PopArcher( const Vector& pos );
	virtual ~PopArcher( );
public:
	void update( );
private:
	int _count;
	EnemyWeakPtr _enemy;
};