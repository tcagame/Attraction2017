#include "RockEventObaba.h"

const int RADIUS = 30;
const int HEIGHT = 30;

RockEventObaba::RockEventObaba(const Vector & pos) :
	RockEventCharacter( pos, DOLL_OBABA, RADIUS, HEIGHT, true ) {
}

RockEventObaba:: ~RockEventObaba( ) {
}