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
	std::vector< std::string > filenames = getFilenames( );
	int size = ( int )filenames.size( );
	_models = { };
	for ( int i = 0; i < size; i++ ) {
		ModelMV1Ptr model( new ModelMV1 );
		model->load( filenames[ i ].c_str( ) );
		_models.push_back( model );
	}
	_col_model = ModelMV1Ptr( new ModelMV1 );
	_col_model->load( "Resource/Rock/map/map01_col.mv1" );
}

void RockMap::update( ) {
}

std::vector< ModelMV1Ptr > RockMap::getModels( ) const {
	return _models;
}

ModelMV1Ptr RockMap::getColModel( ) const {
	return _col_model;
}

