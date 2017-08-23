#include "RockAlter.h"
#include "RockDollHouse.h"
#include "ModelMV1.h"

static const int RANGE = 80;

RockAlter::RockAlter( const Vector& pos ) :
_pos( pos ),
_active( true ) {
}


RockAlter::~RockAlter( ) {
}

bool RockAlter::isInRange( const Vector& pos ) const {
	bool result = false;
	if ( ( pos - _pos ).getLength2( ) < RANGE * RANGE ) {
		result = true;
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
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( doll );
	model->setTrans( Matrix::makeTransformTranslation( _pos ) );
	return model;
}
