#include "RockItemToku.h"
#include "RockDollHouse.h"


RockItemToku::RockItemToku( const Vector& pos ) :
RockItem( pos, DOLL_TOKU ) {
}


RockItemToku::~RockItemToku( ) {
}

ModelMV1Ptr RockItemToku::getModel( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	model->setTrans( Matrix::makeTransformTranslation( getPos( ) ) );
	return model;
}
