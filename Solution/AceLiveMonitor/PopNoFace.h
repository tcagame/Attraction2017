#pragma once
#include "Pop.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Enemy );

class PopNoFace : public Pop {
public:
	PopNoFace( const Vector& pos );
	virtual ~PopNoFace( );
public:
	void update( );
private:
	int _count;
	EnemyWeakPtr _enemy;
};

