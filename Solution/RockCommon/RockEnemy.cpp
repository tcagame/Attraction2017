#include "RockEnemy.h"



RockEnemy::RockEnemy( const Vector& pos, DOLL id, int force, bool mass ) :
RockCharacter( pos, id, mass ),
_force( 1 ) {
}


RockEnemy::~RockEnemy( ) {
}

int RockEnemy::getForce( ) const {
	return _force;
}