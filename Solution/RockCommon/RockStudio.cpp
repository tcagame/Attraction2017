#include "RockStudio.h"
#include "Application.h"
#include "Effect.h"

RockStudioPtr RockStudio::getTask( ) {
	return std::dynamic_pointer_cast< RockStudio >( Application::getInstance( )->getTask( getTag( ) ) );
}


RockStudio::RockStudio( ) {
}

RockStudio::~RockStudio( ) {
}

void RockStudio::initialize( ) {
	EffectPtr effect( Effect::getTask( ) );
	_effect[ EFFECT_SHOT ] = effect->loadEffect( "player_shot.efk" );
	_effect[ EFFECT_CHARGE_SHOT ] = effect->loadEffect( "player_charge_shot.efk" );
	_effect[ EFFECT_CHARGE ] = effect->loadEffect( "charge.efk" );
	_effect[ EFFECT_ANCESTORS_SHOT ] = effect->loadEffect( "ancestors_shot.efk" );
	_effect[ EFFECT_IMPACT ] = effect->loadEffect( "impact.efk" );
}

void RockStudio::update( ) {
}

int RockStudio::getEffectHandle( int id ) {
	return _effect[ id ];
}