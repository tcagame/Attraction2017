#include "RockItemDango.h"
#include "RockDollHouse.h"

const int PRICE = 10000;

RockItemDango::RockItemDango( const Vector& pos ) :
RockItem( pos, DOLL_DANGO, PRICE ) {
}


RockItemDango::~RockItemDango( ) {
}

ModelMV1Ptr RockItemDango::getModel( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	model->setRot( Matrix::makeTransformRotation( Vector( 0, 0, 1 ), PI * 20 / 180 ) );
	model->setTrans( Matrix::makeTransformTranslation( getPos( ) ) );
	return model;
}

