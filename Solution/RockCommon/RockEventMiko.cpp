#include "RockEventMiko.h"

const int RADIUS = 30;
const int HEIGHT = 30;

RockEventMiko::RockEventMiko( const Vector& pos ) :
RockEventCharacter( pos, DOLL_MIKO, RADIUS, HEIGHT, true ) {
}


RockEventMiko::~RockEventMiko( ) {
}
