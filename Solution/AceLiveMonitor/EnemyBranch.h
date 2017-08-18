#pragma once
#include "Enemy.h"
#include "smart_ptr.h"
#include "EnemyAttack.h"
#include <list>

PTR( Enemy );

class EnemyBranch : public EnemyAttack {
public:
	EnemyBranch( const Vector& pos );
	virtual ~EnemyBranch( );
public:
	Chip getChip( ) const;
protected:
	void act( );
private:
	std::list< EnemyPtr > _seeds;
};

