#include "RockCasket.h"
#include "RockDollHouse.h"

RockCasket::RockCasket( const Vector& pos ) :
RockCharacter( pos, DOLL_CASKET, 30, 30, true, false, false ) {
}


RockCasket::~RockCasket( ) { 
}

ModelMV1Ptr RockCasket::getModel( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	model->setTrans( Matrix::makeTransformTranslation( getPos( ) ) );
	return model;
}

void RockCasket::act( ) {
}
