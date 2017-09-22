#pragma once
#include "EnemyAttack.h"
class EnemyBloodDaemonAttack : public EnemyAttack {
public:
	EnemyBloodDaemonAttack( const Vector& pos, int pattern );
	virtual ~EnemyBloodDaemonAttack( );
public:
	void setSynchronousData( int camera_pos ) const;
protected:
	void act( );
private:
	int _pattern;
};

