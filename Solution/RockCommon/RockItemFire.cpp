#include "RockItemFire.h"
#include "RockDollHouse.h"


RockItemFire::RockItemFire( const Vector& pos ) :
RockItem( pos, DOLL_SACRED_FIRE ) {
}


RockItemFire::~RockItemFire( ) {
}

ModelMV1Ptr RockItemFire::getModel( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	Vector pos = getPos( ) + Vector( 0, 15, 0 );
	model->setTrans( Matrix::makeTransformTranslation( pos ) );
	return model;
}
