#pragma once
#include "mathmatics.h"
#include "ace_define.h"
#include "Character.h"

class Impact {
public:
	Impact( const Vector& pos, AREA area = AREA_STREET, int sprite_size = 128 );
	virtual ~Impact( );
public:
	void update( );
	void setSynchronousData( int camera_pos ) const;
	bool isFinished( ) const;
	AREA getArea( ) const;
private:
	Vector _pos;
	int _anim_count;
	AREA _area;
	int _sprite_size;
};

