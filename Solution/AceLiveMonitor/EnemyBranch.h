#pragma once
#include "Enemy.h"
#include "smart_ptr.h"
#include <list>

PTR( Enemy );

class EnemyBranch : public Enemy {
public:
	EnemyBranch( const Vector& pos );
	virtual ~EnemyBranch( );
public:
	Chip getChip( ) const;
protected:
	void act( );
	void damage( int force );
private:
	std::list< EnemyPtr > _seeds;
};

