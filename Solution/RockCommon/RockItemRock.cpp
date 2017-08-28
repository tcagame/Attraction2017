#include "RockItemRock.h"
#include "RockDollHouse.h"

RockItemRock::RockItemRock( const Vector& pos ) :
RockItem( pos, DOLL_SACRED_ROCK ) {
}


RockItemRock::~RockItemRock( ) {
}

ModelMV1Ptr RockItemRock::getModel( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	model->setTrans( Matrix::makeTransformTranslation( getPos( ) ) );
	return model;
}
