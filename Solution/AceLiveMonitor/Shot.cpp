#include "Shot.h"

const int SHOT_SPEED = 10; 
const int VANISH_LENGTH = 500;

Shot::Shot( const Vector& pos, DIR dir, int power ) :
_dir( dir ),
_pos( pos ),
_power( power ),
_count( 0 ) {
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
	_count++;
}

DIR Shot::getDir( ) const {
	return _dir;
}

int Shot::getPower( ) const {
	return _power;
}

int Shot::getCount( ) const {
	return _count;
}

bool Shot::isFinish( ) const {
	return ( _count * _vec.getLength( ) > VANISH_LENGTH );
}