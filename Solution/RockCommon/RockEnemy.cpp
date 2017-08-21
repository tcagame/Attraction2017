#include "RockEnemy.h"
#include "RockPlayer.h"
#include "RockDollHouse.h"

RockEnemy::RockEnemy( const Vector& pos, DOLL doll, int hp, int force, int radius, int height, bool mass, bool head ) :
RockCharacter( pos, doll, radius, height, mass, head ),
_force( 1 ),
_hp( hp ),
_finished( false ),
_max_hp( hp ),
_start_pos( pos ) {
}


RockEnemy::~RockEnemy( ) {
}

void RockEnemy::reset( ) {
	setPos( _start_pos );
	_hp = _max_hp;
	_finished = false;
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

ModelMV1Ptr RockEnemy::getModel( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	model->setAnimTime( getAnimTime( ) );
	double rot = Vector( 0, 0, -1 ).angle( getDir( ) );
	Vector axis = Vector( 0, 1, 0 );
	if ( Vector( 0, 0, -1 ).cross( getDir( ) ).y < 0 ) {
		axis = Vector( 0, -1, 0 );
	}
	model->setRot( Matrix::makeTransformRotation( axis, rot ) );
	model->setTrans( Matrix::makeTransformTranslation( getPos( ) ) );
	return model;
}