#include "RockItemEnhanceCharge.h"
#include "RockItemBubble.h"
#include "RockStorage.h"
#include "RockDollHouse.h"

const int PRICE = 5000;

RockItemEnhanceCharge::RockItemEnhanceCharge( const Vector& pos  ) :
RockItem( pos, DOLL_ENHANCE_CHARGE, PRICE ) {
	_bubble = RockItemBubblePtr( new RockItemBubble( getPos( ) - Vector( 0, 30, 0 ) ) );
	_bubble->setRepop( true );
	RockStorage::getTask( )->addBubble( _bubble );
}


RockItemEnhanceCharge::~RockItemEnhanceCharge( ) {
}

ModelMV1Ptr RockItemEnhanceCharge::getModel( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	model->setTrans( Matrix::makeTransformTranslation( getPos( ) ) );
	return model;
}

void RockItemEnhanceCharge::eraseBubble( ) {
	_bubble->setFinished( true );
}

double RockItemEnhanceCharge::getAnimTime( ) const {
	return 0;
}
