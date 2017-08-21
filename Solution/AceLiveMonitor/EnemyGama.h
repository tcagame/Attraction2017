#pragma once
#include "Enemy.h"
#pragma once
#include "Enemy.h"

class EnemyGama : public Enemy {
public:
	EnemyGama( const Vector& pos );
	virtual ~EnemyGama( );
public:
	Chip getChip( ) const;
	void setSynchronousData( unsigned char type, int camera_pos ) const;
protected:
	void act( );
};

