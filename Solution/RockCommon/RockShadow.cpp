#include "RockShadow.h"
#include "Application.h"
#include "ModelMDL.h"
#include "ModelMV1.h"
#include "RockMap.h"

const int FALL_POWER = -30;
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

void RockShadow::set( const Vector& pos, const double scale, const bool adjust ) {
	Vector ground_pos = adjust ? getAdjustPos( pos ) : pos;
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

	ModelMDLPtr shadow = ModelMDLPtr( new ModelMDL );
	shadow->alloc( 2 );
	shadow->set( 0, vertex[ 0 ] );
	shadow->set( 1, vertex[ 1 ] );
	shadow->set( 2, vertex[ 2 ] );
	shadow->set( 3, vertex[ 1 ] );
	shadow->set( 4, vertex[ 3 ] );
	shadow->set( 5, vertex[ 2 ] );
	shadow->setTexture( GRAPH_PATH.c_str( ) );
	shadow->setTrans( true );
	_models.push_back( shadow );
}

std::list< ModelMDLPtr > RockShadow::getShadows( ) const {
	return _models;
}

void RockShadow::clear( ) {
	_models.clear( );
}

Vector RockShadow::getAdjustPos( const Vector& pos ) {
	Vector result = pos;
	std::vector< ModelMV1Ptr > col_models = RockMap::getTask( )->getColModels( );
	int size = ( int )col_models.size( );
	for ( int i = 0; i < size; i++ ) {
		while ( result.y > -100 ) {
			Vector fpos = result + Vector( 0, FALL_POWER, 0 );
			Vector hit_pos = col_models[ i ]->getHitPos( result, fpos );
			if ( !hit_pos.isOrijin( ) ) {
				result.y = hit_pos.y - result.y;
				break;
			} else {
				result.y += FALL_POWER;
			}
		}
	}
	return result;
}
