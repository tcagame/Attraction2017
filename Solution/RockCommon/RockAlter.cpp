#include "RockAlter.h"
#include "RockDollHouse.h"
#include "ModelMV1.h"

static const int RANGE = 80;

RockAlter::RockAlter( const Vector& pos, const Vector& dir ) :
_pos( pos ),
_dir( dir.normalize( ) ),
_active( true ) {
}


RockAlter::~RockAlter( ) {
}

bool RockAlter::isInRange( const Vector& pos ) const {
	bool result = false;
	Vector distance = pos - _pos;
	if ( distance.angle( _dir ) < PI / 6 ) {
		if ( distance.getLength2( ) < RANGE * RANGE ) {
			result = true;
		}
	}
	return result;
}

bool RockAlter::isActive( ) const {
	return _active;
}

void RockAlter::setActive( bool active ) {
	_active = active;
}

ModelMV1Ptr RockAlter::getModel( ) const {
	DOLL doll = DOLL_ALTER_BEFORE;
	if ( !_active ) {
		doll = DOLL_ALTER_AFTER;
	}
	double rot = Vector( 0, 0, -1 ).angle( _dir );
	Vector axis = Vector( 0, 1, 0 );
	if ( Vector( 0, 0, -1 ).cross( _dir ).y < 0 ) {
		axis = Vector( 0, -1, 0 );
	}
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( doll );
	model->setRot( Matrix::makeTransformRotation( axis, rot ) );
	model->setTrans( Matrix::makeTransformTranslation( _pos ) );
	return model;
}
