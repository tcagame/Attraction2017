#include "Shot.h"



Shot::Shot( const Vector& pos, int power ) :
Character( pos, NORMAL_CHAR_GRAPH_SIZE, 3, false ),
_pos( pos ),
_origin_pos( pos ),
_power( power ),
_finished( false ) {
	setOverlappedRadius( 20 );
}

Shot::~Shot( ) {
}

int Shot::getPower( ) const {
	return _power;
}

Vector Shot::getOriginPos( ) const {
	return _origin_pos;
}

void Shot::erase( ) {
	_finished = true;
}

bool Shot::isFinished( ) const {
	return _finished;
}