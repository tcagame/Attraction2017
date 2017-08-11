#include "RockEnemy.h"
#include "RockPlayer.h"


RockEnemy::RockEnemy( const Vector& pos, DOLL id, int force, int radius, bool mass, bool head ) :
RockCharacter( pos, id, radius, mass, head ),
_force( 1 ) {
}


RockEnemy::~RockEnemy( ) {
}

int RockEnemy::getForce( ) const {
	return _force;
}