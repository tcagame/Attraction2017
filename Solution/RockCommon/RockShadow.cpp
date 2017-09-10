#include "RockShadow.h"
#include "Application.h"
#include "ModelMDL.h"
#include "ModelMV1.h"
#include "RockMap.h"

const int FALL_POWER = -200;
const std::string GRAPH_PATH = "Resource/Rock/shadow/shadow.png";

RockShadowPtr RockShadow::getTask( ) {
	return  std::dynamic_pointer_cast< RockShadow >( Application::getInstance( )->getTask( getTag( ) ) );
}

RockShadow::RockShadow( ) {
}


RockShadow::~RockShadow( ) {
}

void RockShadow::update( ) {
}

int RockShadow::create( const Vector& pos, const double scale ) {
	ModelMDLPtr shadow = ModelMDLPtr( new ModelMDL );	
	createShadow( shadow, pos, scale );
	shadow->setTexture( GRAPH_PATH.c_str( ) );
	shadow->setTrans( true );
	_models.push_back( shadow );
	return ( int )_models.size( ) - 1;
}

void RockShadow::set( const int idx, const Vector& pos, const double scale ) {	
	ModelMDLPtr shadow = _models[ idx ];
	shadow->reset( );
	createShadow( shadow, pos, scale );
}

void RockShadow::createShadow( ModelMDLPtr model, const Vector& pos, const double scale ) {
	Vector ground_pos = getAdjustPos( pos );
	ModelMDL::VERTEX vertex[ 4 ];
	vertex[ 0 ].pos = ground_pos + Vector( -( scale / 2 ), 0, -( scale / 2 ) );
	vertex[ 1 ].pos = ground_pos + Vector(  ( scale / 2 ), 0, -( scale / 2 ) );
	vertex[ 2 ].pos = ground_pos + Vector( -( scale / 2 ), 0,  ( scale / 2 ) );
	vertex[ 3 ].pos = ground_pos + Vector(  ( scale / 2 ), 0,  ( scale / 2 ) );
	
	vertex[ 0 ].u = 0;
	vertex[ 0 ].v = 0;
	vertex[ 1 ].u = 1;
	vertex[ 1 ].v = 0;
	vertex[ 2 ].u = 0;
	vertex[ 2 ].v = 1;
	vertex[ 3 ].u = 1;
	vertex[ 3 ].v = 1;

	model->alloc( 2 );
	model->set( 0, vertex[ 0 ] );
	model->set( 1, vertex[ 1 ] );
	model->set( 2, vertex[ 2 ] );
	model->set( 3, vertex[ 1 ] );
	model->set( 4, vertex[ 3 ] );
	model->set( 5, vertex[ 2 ] );
}

std::vector< ModelMDLPtr > RockShadow::getShadows( ) const {
	return _models;
}

Vector RockShadow::getAdjustPos( const Vector& pos ) {
	Vector result = pos;
	std::vector< ModelMV1Ptr > col_models = RockMap::getTask( )->getColModels( );
	int size = ( int )col_models.size( );
	for ( int i = 0; i < size; i++ ) {
		Vector fpos = result + Vector( 0, FALL_POWER, 0 );
		Vector hit_pos = col_models[ i ]->getHitPos( result, fpos );
		if ( !hit_pos.isOrijin( ) ) {
			result.y = hit_pos.y;
		}
	}
	return result;
}
