#pragma once
#include "Shot.h"

class ShotPlayer : public Shot {
public:
	ShotPlayer( const PLAYER player, const Vector& pos, DIR dir, int level, bool normal );
	virtual ~ShotPlayer( );
public:
	void erase( );
	bool isNormal( );
protected:
	void act( );
	void setSynchronousData( int camera_pos ) const;
private:
	const bool _normal;
	const PLAYER _player;
	const int _level;
};

