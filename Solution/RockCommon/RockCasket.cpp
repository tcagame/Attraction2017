#include "RockCasket.h"
#include "RockDollHouse.h"
#include "RockStudio.h"
#include "Effect.h"

RockCasket::RockCasket( const Vector& pos ) :
RockCharacter( pos, DOLL_CASKET, 30, 30, true, false, true ) {
}


RockCasket::~RockCasket( ) { 
}

ModelMV1Ptr RockCasket::getModel( ) const {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	model->setTrans( Matrix::makeTransformTranslation( getPos( ) ) );
	model->setScale( Matrix::makeTransformScaling( Vector( 1, 1, 1 ) * 1 ) );
	return model;
}

void RockCasket::act( ) {
}

RockCasket::RESULT RockCasket::getOpenResult( ) const {
	RESULT result = RESULT_SUCCESS;
	EffectPtr effect = Effect::getTask( );
	srand( 3 );
	if( rand( ) % 3 == 0 ) {
		effect->updateEffectTransform( effect->playEffect( RockStudio::getTask( )->getEffectHandle( EFFECT_CASKET_BAD ) ), getPos( ) );
		result = RESULT_BAD;
	} else {
		effect->updateEffectTransform( effect->playEffect( RockStudio::getTask( )->getEffectHandle( EFFECT_CASKET_SUCCESS ) ), getPos( ) );
	}
	return result;
}