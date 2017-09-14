#include "RockEventOtohime.h"

const int RADIUS = 20;
const int HEIGHT = 30;

RockEventOtohime::RockEventOtohime( const Vector& pos ) :
RockEventCharacter( pos, DOLL_OTOHIME, RADIUS, HEIGHT, true ) {
	setDir( Vector( 1, 0, 0 ) );
}


RockEventOtohime::~RockEventOtohime( ) {
}
