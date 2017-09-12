#pragma once
#include "Shot.h"

class ShotPlayer : public Shot {
public:
	ShotPlayer( const PLAYER player, const Vector& pos, DIR dir, int level );
	virtual ~ShotPlayer( );
public:
	void erase( );
protected:
	void act( );
	void setSynchronousData( unsigned char type, int camera_pos ) const;
private:
	PLAYER _player;
	int _level;
};

