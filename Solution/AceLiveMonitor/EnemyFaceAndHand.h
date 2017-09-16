#pragma once
#include "Enemy.h"

class EnemyFaceAndHand : public Enemy {
public:
	EnemyFaceAndHand( const Vector& pos );
	virtual ~EnemyFaceAndHand( );
public:
	void setSynchronousData( int camera_pos ) const;
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

