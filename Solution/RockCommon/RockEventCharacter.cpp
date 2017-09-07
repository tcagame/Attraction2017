#include "RockEventCharacter.h"
#include "RockDollHouse.h"

RockEventCharacter::RockEventCharacter( const Vector& pos, DOLL doll, int radius, int height, bool mass ) :
RockCharacter( pos, doll, radius, height, mass ) {
}


RockEventCharacter::~RockEventCharacter( ) {
}

void RockEventCharacter::damage( int force ) {
	if ( force < 0 ) {
		RockCharacter::damage( force );
	}
}

ModelMV1Ptr RockEventCharacter::getModel( ) const {
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

double RockEventCharacter::getAnimTime( ) const {
	return 0;
}
