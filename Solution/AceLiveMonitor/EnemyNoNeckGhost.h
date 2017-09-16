#pragma once
#include "Enemy.h"

class EnemyNoNeckGhost : public Enemy {
public:
	EnemyNoNeckGhost( const Vector& pos );
	virtual ~EnemyNoNeckGhost( );
public:
	void setSynchronousData( int camera_pos ) const;
protected:
	void act( );
private:
	int _vy;
	int _dir;
};

