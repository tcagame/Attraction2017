#pragma once
#include "Enemy.h"

class EnemyWhiteMist : public Enemy {
public:
	EnemyWhiteMist( const Vector& pos );
	virtual ~EnemyWhiteMist( );
public:
	void setSynchronousData( unsigned char type, int camera_pos ) const;
protected:
	void act( );
private:
	int _vy;
	int _dir;
	Vector _origin_pos;
};

