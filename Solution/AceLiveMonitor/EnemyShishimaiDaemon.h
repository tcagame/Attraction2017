#pragma once
#include "Enemy.h"

class EnemyShishimaiDaemon : public Enemy {
public:
	EnemyShishimaiDaemon( const Vector& pos );
	virtual ~EnemyShishimaiDaemon( );
public:
	void setSynchronousData( int camera_pos ) const;
protected:
	void act( );
private:
	bool _escape;
	Vector _befor_pos;
};

