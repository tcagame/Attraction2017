#include "RockMapResult.h"
#include "ModelMV1.h"
#include "Effect.h"
#include "RockStudio.h"

RockMapResult::RockMapResult( ) {
}


RockMapResult::~RockMapResult( ) {
}

void RockMapResult::initialize( ) {
	ModelMV1Ptr map01 = ModelMV1Ptr( new ModelMV1 );
	map01->load( "Resource/Rock/map/result/map11_01.mv1" );
	addModel( map01 );
	
	ModelMV1Ptr col01 = ModelMV1Ptr( new ModelMV1 );
	col01->load( "Resource/Rock/map/result/map11_01.mv1" );
	col01->draw( );
	addColModel( col01 );

	//”wŒi
	ModelMV1Ptr map03 = ModelMV1Ptr( new ModelMV1 );
	map03->load( "Resource/Rock/map/result/map11_03.mv1" );
	addModel( map03 );

	ModelMV1Ptr map05 = ModelMV1Ptr( new ModelMV1 );
	map05->load( "Resource/Rock/map/result/map11_05.mv1" );
	addModel( map05 );

	ModelMV1Ptr map04 = ModelMV1Ptr( new ModelMV1 );
	map04->load( "Resource/Rock/map/result/map11_04.mv1" );
	addModel( map04 );

	ModelMV1Ptr map02 = ModelMV1Ptr( new ModelMV1 );
	map02->load( "Resource/Rock/map/result/map11_02.mv1" );
	addModel( map02 );

	_darw_butta = false;

}

void RockMapResult::update( ) {
	EffectPtr effect = Effect::getTask( );
	if ( !_darw_butta ) {
		effect->updateEffectTransform( effect->playEffect( RockStudio::getTask( )->getEffectHandle( EFFECT_BUTTA ) ), Vector( 500, 250, 0 ) );
		_darw_butta = true;
	}
}
