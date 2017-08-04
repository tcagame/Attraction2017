#include "RockMap.h"
#include "Application.h"
	
RockMapPtr RockMap::getTask( ) {
	return std::dynamic_pointer_cast<RockMap>( Application::getInstance( )->getTask( getTag( ) ) );
}



RockMap::RockMap( ) {
}


RockMap::~RockMap( ) {
}

void RockMap::initialize( ) {	
	_model = ModelMV1Ptr( new ModelMV1 );
	_col_model = ModelMV1Ptr( new ModelMV1 );
	_model->load( "Resource/Rock/map/map01.mv1" );
	_col_model->load( "Resource/Rock/map/map01_col.mv1" );
}

ModelMV1Ptr RockMap::getModel( ) const {
	return _model;
}

ModelMV1Ptr RockMap::getColModel( ) const {
	return _col_model;
}

void RockMap::update( ) {
}
