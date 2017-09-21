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
	model->setRot( Matrix::makeTransformRotation( Vector( 0, -1, 0 ), PI / 2 ) );
	return model;
}

void RockItemTree::eraseBubble( ) {
	_bubble->setFinished( true );
}

double RockItemTree::getAnimTime( ) const {
	return 0;
}

void RockItemTree::act() {
	_bubble->setPos(getPos());
}