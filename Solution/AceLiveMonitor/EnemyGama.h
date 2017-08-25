#pragma once
#include "Enemy.h"

class EnemyGama : public Enemy {
public:
	EnemyGama( const Vector& pos );
	virtual ~EnemyGama( );
public:
	void setSynchronousData( unsigned char type, int camera_pos ) const;
protected:
	void act( );
	void damage( int force );
private:
	bool _guide;
};

