#pragma once
#include "Enemy.h"

class EnemyCrocoSnake : public Enemy {
public:
	EnemyCrocoSnake( const Vector& pos );
	virtual ~EnemyCrocoSnake( );
public:
	void setSynchronousData( unsigned char type, int camera_pos ) const;
protected:
	void act( );
private:
	Vector _before_pos;
};

