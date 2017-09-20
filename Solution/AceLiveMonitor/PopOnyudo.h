#pragma once
#include "Pop.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Enemy );

class PopOnyudo : public Pop {
public:
	PopOnyudo( const Vector& pos );
	virtual ~PopOnyudo( );
public:
	void update( );
private:
	int _count;
	EnemyWeakPtr _enemy;
};

