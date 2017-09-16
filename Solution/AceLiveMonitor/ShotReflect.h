#pragma once
#include "Shot.h"
class ShotReflect : public Shot {
public:
	ShotReflect( PLAYER player, const Vector& pos );
	virtual ~ShotReflect( );
public:
	void setSynchronousData( int camera_pos ) const;
protected:
	void act( );
private:
	PLAYER _player;
};

