#include "Shot.h"

static const int MAX_HP = 3;

Shot::Shot( const Vector& pos, DIR dir, int power ) :
Character( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP, false ),
_dir( dir ),
_pos( pos ),
_origin_pos( pos ),
_power( power ) {
	setRadius( 20 );
}

Shot::~Shot( ) {
}

DIR Shot::getDir( ) const {
	return _dir;
}

int Shot::getPower( ) const {
	return _power;
}

void Shot::setPower( int power ) {
	_power = power;
}

Vector Shot::getOriginPos( ) const {
	return _origin_pos;
}
