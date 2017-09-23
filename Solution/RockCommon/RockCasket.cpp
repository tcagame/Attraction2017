#include "RockCasket.h"
#include "RockDollHouse.h"
#include "RockStudio.h"
#include "Effect.h"

RockCasket::RockCasket( const Vector& pos ) :
RockCharacter( pos, DOLL_CASKET, 30, 30, false, false, true ) {
	setVec( Vector( 0, -1, 0 ) );
	setDir( Vector( 1, 0, 0 ) );
	_rot = 0;
}


RockCasket::~RockCasket( ) { 
}

ModelMV1Ptr RockCasket::getModel( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	model->setTrans( Matrix::makeTransformTranslation( getPos( ) ) );
	model->setScale( Matrix::makeTransformScaling( Vector( 1, 1, 1 ) * 1 ) );
	//double rot = Vector( 0, 0, -1 ).angle( getDir( ) );
	Vector axis = Vector( 0, 1, 0 );
	//if ( Vector( 0, 0, -1 ).cross( getDir( ) ).y < 0 ) {
	//	axis = Vector( 0, -1, 0 );
	//}
	model->setRot( Matrix::makeTransformRotation( axis, _rot ) );
	return model;
}

void RockCasket::act( ) {
	_rot += PI / 80;
}

RockCasket::RESULT RockCasket::getOpenResult( ) const {
	RESULT result = RESULT_SUCCESS;
	EffectPtr effect = Effect::getTask( );
	srand( 3 );
	if( rand( ) % 7 == 0 ) {
		effect->updateEffectTransform( effect->playEffect( RockStudio::getTask( )->getEffectHandle( EFFECT_CASKET_BAD ) ), getPos( ) );
		result = RESULT_BAD;
	} else {
		effect->updateEffectTransform( effect->playEffect( RockStudio::getTask( )->getEffectHandle( EFFECT_CASKET_SUCCESS ) ), getPos( ) );
	}
	return result;
}