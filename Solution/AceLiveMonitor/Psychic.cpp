#include "Psychic.h"

const int PSYCHIC_SPEED = 10; 

Psychic::Psychic( const Vector& pos, Player::DIR dir ) {
	_pos = pos;
	if ( dir == Player::DIR_LEFT ) {
		_dir = -1;
	}
	if ( dir == Player::DIR_RIGHT ) {
		_dir = 1;
	}
}

Psychic::~Psychic( ) {
}

Vector Psychic::getPos( ) const {
	return _pos;
}

void Psychic::update( ) {
	
	_pos.x += PSYCHIC_SPEED * _dir;
}

int Psychic::getDir( ) {
	return _dir;
}




