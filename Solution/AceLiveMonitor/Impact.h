#pragma once
#include "mathmatics.h"
#include "ace_define.h"
#include "Character.h"

class Impact {
public:
	Impact( const Vector& pos, Character::STATE state = Character::STATE_MAIN, int sprite_size = 128 );
	virtual ~Impact( );
public:
	void update( );
	Chip getChip( ) const;
	bool isFinished( ) const;
	Character::STATE getState( ) const;
private:
	Vector _pos;
	int _anim_count;
	Character::STATE _state;
	int _sprite_size;
};

