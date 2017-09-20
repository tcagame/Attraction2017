#pragma once
#include "Pop.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Enemy );

class PopShell : public Pop {
public:
	PopShell( const Vector& pos );
	virtual ~PopShell( );
public:
	void update( );
private:
	int _count;
	EnemyWeakPtr _enemy;
};

