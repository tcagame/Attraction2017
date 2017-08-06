#include "RockStreet.h"
#include "Application.h"

RockStreetPtr RockStreet::getTask( ) {
	return std::dynamic_pointer_cast<RockStreet>( Application::getInstance( )->getTask( getTag( ) ) );
}

RockStreet::RockStreet( ) {
}

RockStreet::~RockStreet( ) {
}

void RockStreet::initialize( ) {
	for ( int i = 0; i < STREET_MODEL_NUM; i++ ) {
		_model[ i ] = ModelMV1Ptr( new ModelMV1 );
		char filename[ 256 ];
		sprintf_s( filename, "../Resource/Rock/map/map02_0%d.mv1", i + 1 );
		_model[ i ]->load( filename );
	}
}

void RockStreet::update( ) {
	draw( );
}

void RockStreet::draw( ) {
	for ( int i = 0; i < STREET_MODEL_NUM; i++ ) {
		_model[ i ]->draw( );
	}
}
