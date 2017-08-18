#include "RockEnemy.h"
#include "RockPlayer.h"


RockEnemy::RockEnemy( const Vector& pos, DOLL id, int hp, int force, int radius, int height, bool mass, bool head ) :
RockCharacter( pos, id, radius, height, mass, head ),
_force( 1 ),
_hp( hp ),
_finished( false ) {
}


RockEnemy::~RockEnemy( ) {
}

int RockEnemy::getForce( ) const {
	return _force;
}

void RockEnemy::damage( int force ) {
	if ( force < 0 ) {
		_hp = 0;
		_finished = true;
		return;
	}

	_hp -= force;
	if ( _hp < 0 ) {
		_hp = 0;
		_finished = true;
	}
}

bool RockEnemy::isFinished( ) const {
	return _finished;
}