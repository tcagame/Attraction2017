#pragma once
#include "Pop.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Enemy )

class PopStone : public Pop {
public:
	PopStone( const Vector& pos );
	virtual ~PopStone( );
public:
	void update( );
private:
	EnemyWeakPtr _enemy;
};

