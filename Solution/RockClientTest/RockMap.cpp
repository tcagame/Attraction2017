#include "RockMap.h"
#include "Application.h"
	
RockMapPtr RockMap::getTask( ) {
	return std::dynamic_pointer_cast<RockMap>( Application::getInstance( )->getTask( getTag( ) ) );
}



RockMap::RockMap( ) {
}


RockMap::~RockMap( ) {
}

ModelMV1Ptr RockMap::getModel( ) {
	return _model;
}

void RockMap::initialize( ) {	
	_model = ModelMV1Ptr( new ModelMV1 );
	_model->load( "Resource/Rock/map/map01.mv1" );
}

void RockMap::update( ) {
}
