#include "Shot.h"

static const int SHOT_SPEED = 10; 
static const int MAX_HP = 3;

Shot::Shot( const Vector& pos, DIR dir, int power ) :
Character( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP, false ),
_dir( dir ),
_pos( pos ),
_power( power ) {
	Vector vec = Vector( SHOT_SPEED, 0 );
	if ( dir == DIR_LEFT ) {
		vec.x *= -1;
	}
	setVec( vec );
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
