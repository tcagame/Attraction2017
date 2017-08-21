#pragma once
#include "Enemy.h"

class EnemyBlueMonk : public Enemy {
public:
	EnemyBlueMonk( const Vector& pos );
	virtual ~EnemyBlueMonk( );
public:
	Chip getChip( ) const;
	void setSynchronousData( unsigned char type, int camera_pos ) const;
protected:
	void act( );
private:
	Vector _before_pos;
	Vector _vec;
};

