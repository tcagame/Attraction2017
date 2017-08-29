#include "RockBubble.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockDollHouse.h"

const double MODEL_SIZE = 1.0;
const Vector FOOT = Vector( 0, -20, 0 );


RockBubble::RockBubble( int id ) :
_id( id ) {
}


RockBubble::~RockBubble( ) {
}

void RockBubble::update( ) {
	RockPlayerPtr player = RockFamily::getTask( )->getPlayer( _id );
	_active = false;
	if ( player->isDead( ) ) {
		_active = true;
		_pos = player->getPos( ) + FOOT;
	}
}

bool RockBubble::isActive( ) const {
	return _active;
}


ModelMV1Ptr RockBubble::getModel( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( DOLL_BUBBLE );
	model->setTrans( Matrix::makeTransformTranslation( _pos ) );
	model->setScale( Matrix::makeTransformScaling( Vector( 1, 1, 1 ) * MODEL_SIZE ) );
	return model;
}
