#include "Shot.h"

const int SHOT_SPEED = 10; 

Shot::Shot( const Vector& pos, Player::DIR dir ) {
	_pos = pos;
	if ( dir == Player::DIR_LEFT ) {
		_dir = -1;
	}
	if ( dir == Player::DIR_RIGHT ) {
		_dir = 1;
	}
}

Shot::~Shot( ) {
}

Vector Shot::getPos( ) const {
	return _pos;
}

void Shot::update( ) {
	_pos.x += SHOT_SPEED * _dir;
}

int Shot::getDir( ) const {
	return _dir;
}
