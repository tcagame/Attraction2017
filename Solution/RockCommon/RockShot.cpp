#include "RockShot.h"

RockShot::RockShot( const Vector& pos ) :
RockCharacter( pos, DOLL_NONE, 32, 32, false, false ) {
	setVec( Vector( 0.1, 0.1, 0.1 ) );
}


RockShot::~RockShot( ) {
}

int RockShot::getEffectHandle( ) const {
	return EFFECT_SHOT;
}

void RockShot::act( ) {
}

double RockShot::getAnimTime( ) const {
	return 0;
}
