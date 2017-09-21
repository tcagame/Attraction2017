#include "RockItemRock.h"
#include "RockDollHouse.h"
#include "RockStorage.h"
#include "RockItemBubble.h"


RockItemRock::RockItemRock( const Vector& pos ) :
RockItem( pos, DOLL_SACRED_ROCK ) {
	_bubble = RockItemBubblePtr( new RockItemBubble( getPos( ) ) );
	RockStorage::getTask( )->addBubble( _bubble );
}


RockItemRock::~RockItemRock( ) {
}

ModelMV1Ptr RockItemRock::getModel( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	Vector pos = getPos( ) + Vector( 0, 15, 0 );
	model->setTrans( Matrix::makeTransformTranslation( pos ) );
	model->setRot( Matrix::makeTransformRotation( Vector( 0, -1, 0 ), PI / 2 ) );
	return model;
}

void RockItemRock::eraseBubble( ) {
	_bubble->setFinished( true );
}

double RockItemRock::getAnimTime( ) const {
	return 0;
}

void RockItemRock::act() {
	_bubble->setPos( getPos( ) );
}