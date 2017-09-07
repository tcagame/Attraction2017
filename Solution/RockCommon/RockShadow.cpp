#include "RockShadow.h"
#include "Application.h"
#include "ModelMDL.h"

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

void RockShadow::set( const Vector& pos, const double scale ) {
	ModelMDL::VERTEX vertex[ 4 ];
	vertex[ 0 ].pos = pos + Vector( -( scale / 2 ), 0, -( scale / 2 ) );
	vertex[ 1 ].pos = pos + Vector(  ( scale / 2 ), 0, -( scale / 2 ) );
	vertex[ 2 ].pos = pos + Vector( -( scale / 2 ), 0,  ( scale / 2 ) );
	vertex[ 3 ].pos = pos + Vector(  ( scale / 2 ), 0,  ( scale / 2 ) );

	//vertex[ 0 ].pos.z = 0.1;
	//vertex[ 1 ].pos.z = 0.1;
	//vertex[ 2 ].pos.z = 0.1;
	//vertex[ 3 ].pos.z = 0.1;

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
