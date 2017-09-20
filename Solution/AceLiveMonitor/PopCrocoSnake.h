#pragma once
#include "Pop.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Enemy );

class PopCrocoSnake : public Pop {
public:
	PopCrocoSnake( const Vector& pos );
	virtual ~PopCrocoSnake( );
public:
	void update( );
private:
	int _count;
	EnemyWeakPtr _enemy;
};

