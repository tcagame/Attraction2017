#pragma once
#include "Enemy.h"

class EnemyGama : public Enemy {
public:
	EnemyGama( const Vector& pos );
	virtual ~EnemyGama( );
public:
	bool isGuide( ) const;
	void setSynchronousData( int camera_pos ) const;
	Vector getOverlappedPos( ) const;
protected:
	void act( );
	void damage( int force );
private:
	bool _guide;
};

