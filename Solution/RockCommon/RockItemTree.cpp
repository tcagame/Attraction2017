#include "RockItemTree.h"
#include "RockDollHouse.h"
#include "RockStorage.h"
#include "RockItemBubble.h"

RockItemTree::RockItemTree( const Vector& pos ) :
RockItem( pos, DOLL_SACRED_TREE ) {
	_bubble = RockItemBubblePtr( new RockItemBubble( getPos( ) ) );
	RockStorage::getTask( )->addBubble( _bubble );
}


RockItemTree::~RockItemTree( ) {
}

ModelMV1Ptr RockItemTree::getModel( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	Vector pos = getPos( ) + Vector( 0, 15, 0 );
	model->setTrans( Matrix::makeTransformTranslation( pos ) );
	return model;
}

void RockItemTree::eraseBubble( ) {
	_bubble->setFinished( true );
}