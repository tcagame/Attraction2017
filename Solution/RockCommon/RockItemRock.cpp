#include "RockItemRock.h"
#include "RockDollHouse.h"

RockItemRock::RockItemRock( const Vector& pos ) :
RockItem( pos, DOLL_SACRED_ROCK ) {
}


RockItemRock::~RockItemRock( ) {
}

ModelMV1Ptr RockItemRock::getModel( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	Vector pos = getPos( ) + Vector( 0, 15, 0 );
	model->setTrans( Matrix::makeTransformTranslation( pos ) );
	return model;
}
