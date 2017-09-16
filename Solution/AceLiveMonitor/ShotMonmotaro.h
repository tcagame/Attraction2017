#pragma once
#include "Shot.h"

class ShotMonmotaro : public Shot {
public:
	ShotMonmotaro( const PLAYER player, const Vector& pos, DIR dir, int power );
	virtual ~ShotMonmotaro( );
protected:
	void act( );
	void setSynchronousData( int camera_pos ) const;
};

