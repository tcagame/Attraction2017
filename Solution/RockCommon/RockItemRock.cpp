#include "RockItemRock.h"
#include "RockDollHouse.h"
#include "RockStorage.h"
#include "RockItemBubble.h"


RockItemRock::RockItemRock( const Vector& pos ) :
RockItem( pos, DOLL_SACRED_ROCK ) {
	_bubble = RockItemBubblePtr( new RockItemBubble( getPos( ) - Vector( 0, 30, 0 ) ) );
	RockStorage::getTask( )->addBubble( _bubble );
}


RockItemRock::~RockItemRock( ) {
}

ModelMV1Ptr RockItemRock::getModel( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	Vector pos = getPos( ) + Vector( 0, 15, 0 );
	model->setTrans( Matrix::makeTransformTranslation( pos ) );
	return model;
}

void RockItemRock::eraseBubble( ) {
	_bubble->setFinished( true );
}