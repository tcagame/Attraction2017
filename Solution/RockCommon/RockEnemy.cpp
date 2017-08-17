#include "RockEnemy.h"
#include "RockPlayer.h"


RockEnemy::RockEnemy( const Vector& pos, DOLL id, int force, int radius, int height, bool mass, bool head ) :
RockCharacter( pos, id, radius, height, mass, head ),
_force( 1 ),
_finished( false ) {
}


RockEnemy::~RockEnemy( ) {
}

int RockEnemy::getForce( ) const {
	return _force;
}

void RockEnemy::damage( int force ) {
	_finished = true;
}

bool RockEnemy::isFinished( ) const {
	return _finished;
}