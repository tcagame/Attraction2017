#pragma once
#include "Enemy.h"

class EnemyArcher : public Enemy {
public:
	EnemyArcher( const Vector& pos );
	virtual ~EnemyArcher( );
public:
	void setSynchronousData( int camera_pos ) const;
protected:
	void act( );
private:
	enum ACTION {
		ACTION_MOVE,
		ACTION_SHOT,
	};
private:
	ACTION _act;
};

