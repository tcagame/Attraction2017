#pragma once
#include "EnemyAttack.h"
class EnemyRedBirdAttack : public EnemyAttack {
public:
	EnemyRedBirdAttack( const Vector& pos );
	virtual ~EnemyRedBirdAttack( );
public:
	void setSynchronousData( unsigned char type, int camera_pos ) const;
protected:
	void act( );
};

