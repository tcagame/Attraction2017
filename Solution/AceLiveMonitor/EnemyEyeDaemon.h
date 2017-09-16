#pragma once
#include "Enemy.h"

class EnemyEyeDaemon : public Enemy {
public:
	EnemyEyeDaemon( const Vector& pos );
	virtual ~EnemyEyeDaemon( );
public:
	void setSynchronousData( int camera_pos ) const;
protected:
	void act( );
private:
	Vector _before_pos;
	bool _air_jump;
};

