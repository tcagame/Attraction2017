#include "RockItemBubble.h"
#include "RockDollHouse.h"

RockItemBubble::RockItemBubble( const Vector& pos ) :
RockItem( pos, DOLL_BUBBLE ) {
}

RockItemBubble::~RockItemBubble( ) {
}

ModelMV1Ptr RockItemBubble::getModel( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	model->setTrans( Matrix::makeTransformTranslation( getPos( ) ) );
	return model;
}
