#pragma once
#include "Enemy.h"
class EnemyFaceAndHand : public Enemy {
public:
	EnemyFaceAndHand( const Vector& pos );
	virtual ~EnemyFaceAndHand( );
public:
	Chip getChip( ) const;
protected:
	void act( );
private:
	enum ACTION {
		ACTION_FADE_IN,
		ACTION_MOVE,
	};
private:
	ACTION _act;
};
