#include "RockBubble.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockDollHouse.h"

const double MODEL_SIZE = 1.0;

RockBubble::RockBubble( int id ) :
_id( id ) {
}


RockBubble::~RockBubble( ) {
}

void RockBubble::update( ) {
	RockPlayerPtr player = RockFamily::getTask( )->getPlayer( _id );
	_active = false;
	if ( player->isActive( ) ) {
		if ( player->isDead( ) ||
			 player->isBubble( ) ) {
			_active = true;
			_pos = player->getPos( );
		}
	}
}

bool RockBubble::isActive( ) const {
	return _active;
}


ModelMV1Ptr RockBubble::getModel( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( DOLL_BUBBLE );
	static int time = 0;
	time = ( time++ ) % ( int )model->getEndAnimTime( );
	model->setAnimTime( ( double )time );
	model->setTrans( Matrix::makeTransformTranslation( _pos ) );
	model->setScale( Matrix::makeTransformScaling( Vector( 3, 3, 3 ) * MODEL_SIZE ) );
	return model;
}
