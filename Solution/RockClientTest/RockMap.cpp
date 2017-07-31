#include "RockMap.h"
#include "Application.h"

const double MAP_SCALE = 6;

RockMapPtr RockMap::getTask( ) {
	return std::dynamic_pointer_cast< RockMap >( Application::getInstance( )->getTask( getTag( ) ) );
}


RockMap::RockMap( ) {

}


RockMap::~RockMap( ) {
}

void RockMap::initialize( ) {
	_model = ModelMV1Ptr( new ModelMV1 );
	_model->load( "Resource/Rock/map/map01.mv1" );
	_model->scaleTransform( Matrix::makeTransformScaling( Vector( MAP_SCALE, MAP_SCALE, MAP_SCALE ) ) );
}

void RockMap::update( ) {

}
	
ModelMV1Ptr RockMap::getModel( ) {
	return _model;
}
