#pragma once
#include "Enemy.h"

class EnemyJizo : public Enemy {
public:
	EnemyJizo( const Vector& pos );
	virtual ~EnemyJizo( );
public:
	void setSynchronousData( unsigned char type, int camera_pos ) const;
protected:
	void act( );
private:
	enum ACTION {
		ACTION_FADE_IN,
		ACTION_MOVE
	};
private:
	ACTION _act;
	Vector _before_pos;
};

