#pragma once
#include "EnemyAttack.h"
class EnemyTreeNuts : public EnemyAttack {
public:
	EnemyTreeNuts( const Vector& pos );
	virtual ~EnemyTreeNuts( );
public:
	void setSynchronousData( int camera_pos ) const;
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

