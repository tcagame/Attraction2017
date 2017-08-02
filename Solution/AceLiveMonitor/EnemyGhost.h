#pragma once
#include "Enemy.h"

class EnemyGhost : public Enemy {
public:
	EnemyGhost( const Vector& pos );
	virtual ~EnemyGhost( );
public:
	Chip getChip( ) const;
protected:
	void act( );
private:
	enum ACTION {
		ACTION_FADE_IN,
		ACTION_MOVE
	};
private:
	ACTION _act;
};

