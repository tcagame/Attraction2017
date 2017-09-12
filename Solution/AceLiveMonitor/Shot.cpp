#include "Shot.h"

static const int MAX_HP = 3;

Shot::Shot( const Vector& pos, int power ) :
Character( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP, false ),
_pos( pos ),
_origin_pos( pos ),
_power( power ) {
	setRadius( 20 );
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
	setFinished( );
}