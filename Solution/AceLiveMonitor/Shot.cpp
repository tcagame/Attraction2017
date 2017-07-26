#include "Shot.h"

const int SHOT_SPEED = 10; 

Shot::Shot( const Vector& pos, DIR dir ) :
_dir( dir ),
_pos( pos ) {
	_vec = Vector( SHOT_SPEED, 0 );
	if ( dir == DIR_LEFT ) {
		_vec.x *= -1;
	}
}

Shot::~Shot( ) {
}

Vector Shot::getPos( ) const {
	return _pos;
}

void Shot::update( ) {
	_pos += _vec;
}

DIR Shot::getDir( ) const {
	return _dir;
}
