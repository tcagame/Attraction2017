#include "RockItemBubble.h"
#include "RockDollHouse.h"

RockItemBubble::RockItemBubble( const Vector& pos ) :
RockItem( pos, DOLL_BUBBLE ),
_finished( false ) {
}

RockItemBubble::~RockItemBubble( ) {
}

ModelMV1Ptr RockItemBubble::getModel( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	model->setTrans( Matrix::makeTransformTranslation( getPos( ) ) );
	return model;
}

void RockItemBubble::setFinished( bool finish ) {
	_finished = finish;
}

bool RockItemBubble::isFinished( ) const {
	return _finished;
}

double RockItemBubble::getAnimTime( ) const {
	return 0;
}

void RockItemBubble::setPos(const Vector& pos) {
	RockCharacter::setPos( pos );
}