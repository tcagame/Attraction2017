#pragma once
#include "Shot.h"

class ShotPlayer : public Shot {
public:
	ShotPlayer( const Vector& pos, DIR dir, int power );
	virtual ~ShotPlayer( );
protected:
	void act( );
	void setSynchronousData( unsigned char type, int camera_pos ) const;
};

