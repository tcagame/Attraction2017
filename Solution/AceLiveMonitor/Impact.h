#pragma once
#include "mathmatics.h"
#include "ace_define.h"

class Impact {
public:
	Impact( const Vector& pos );
	virtual ~Impact( );
public:
	void update( );
	Chip getChip( ) const;
	bool isFinished( ) const;
private:
	Vector _pos;
	int _anim_count;
};

