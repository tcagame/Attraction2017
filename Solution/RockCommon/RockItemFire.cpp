#include "RockItemFire.h"
#include "RockDollHouse.h"
#include "RockStorage.h"
#include "RockItemBubble.h"


RockItemFire::RockItemFire( const Vector& pos ) :
RockItem( pos, DOLL_SACRED_FIRE ) {
	_bubble = RockItemBubblePtr( new RockItemBubble( getPos( ) - Vector( 0, 30, 0 ) ) );
	RockStorage::getTask( )->addBubble( _bubble );
}


RockItemFire::~RockItemFire( ) {
}

ModelMV1Ptr RockItemFire::getModel( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	Vector pos = getPos( ) + Vector( 0, 15, 0 );
	model->setTrans( Matrix::makeTransformTranslation( pos ) );
	return model;
}

void RockItemFire::eraseBubble( ) {
	_bubble->setFinished( true );
}
