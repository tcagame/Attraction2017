#include "RockItemTree.h"
#include "RockDollHouse.h"


RockItemTree::RockItemTree( const Vector& pos ) :
RockItem( pos, DOLL_SACRED_TREE ) {
}


RockItemTree::~RockItemTree( ) {
}

ModelMV1Ptr RockItemTree::getModel( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	Vector pos = getPos( ) + Vector( 0, 15, 0 );
	model->setTrans( Matrix::makeTransformTranslation( pos ) );
	return model;
}
