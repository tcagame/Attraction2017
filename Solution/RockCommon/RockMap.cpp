#include "RockMap.h"
#include "Application.h"
#include "ModelMV1.h"
	
RockMapPtr RockMap::getTask( ) {
	return std::dynamic_pointer_cast<RockMap>( Application::getInstance( )->getTask( getTag( ) ) );
}



RockMap::RockMap( ) {
}


RockMap::~RockMap( ) {
}

std::vector< ModelMV1Ptr > RockMap::getModels( ) const {
	return _models;
}

std::vector< ModelMV1Ptr > RockMap::getColModels( ) const {
	return _col_models;
}

std::vector< ModelMV1Ptr > RockMap::getBackGroundModels( ) const {
	return _back_ground_models;
}

std::vector< ModelMV1Ptr > RockMap::getCleannessModels( ) const {
	return _cleanness_models;
}

void RockMap::addModel( ModelMV1Ptr model ) {
	_models.push_back( model );
}

void RockMap::addColModel( ModelMV1Ptr model ) {
	_col_models.push_back( model );
}

void RockMap::addBackGroundModel( ModelMV1Ptr model ) {
	_back_ground_models.push_back( model );
}

void RockMap::addCleannessModel( ModelMV1Ptr model ) {
	_cleanness_models.push_back( model );
}

void RockMap::resetModels( ) {
	_models.clear( );
	_col_models.clear( );
	_back_ground_models.clear( );
	_cleanness_models.clear( );
}
