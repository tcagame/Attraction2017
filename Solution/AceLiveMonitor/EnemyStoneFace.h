#pragma once
#include "Enemy.h"

class EnemyStoneFace : public Enemy {
public:
	EnemyStoneFace( const Vector& pos );
	virtual ~EnemyStoneFace( );
public:
	Chip getChip( ) const;
protected:
	void act( );
private:
	enum ACTION {
		ACTION_IN,
		ACTION_MOVE,
	};
private:
	ACTION _action;
};

