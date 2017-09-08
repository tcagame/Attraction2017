#include "RockItemEnhancePower.h"
#include "RockDollHouse.h"
#include "RockStorage.h"
#include "RockItemBubble.h"

static const int PRICE = 5000;

RockItemEnhancePower::RockItemEnhancePower( const Vector& pos  ) :
RockItem( pos, DOLL_ENHANCE_POWER, PRICE ) {
	_bubble = RockItemBubblePtr( new RockItemBubble( getPos( ) - Vector( 0, 30, 0 ) ) );
	_bubble->setRepop( true );
	RockStorage::getTask( )->addBubble( _bubble );
}


RockItemEnhancePower::~RockItemEnhancePower( ) {
}

ModelMV1Ptr RockItemEnhancePower::getModel( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	model->setTrans( Matrix::makeTransformTranslation( getPos( ) ) );
	return model;
}

void RockItemEnhancePower::eraseBubble( ) {
	_bubble->setFinished( true );
}
