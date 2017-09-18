#include "RockShadow.h"
#include "Application.h"
#include "ModelMDL.h"
#include "ModelMV1.h"
#include "RockMap.h"

const int FALL_POWER = -500;
const std::string GRAPH_PATH = "Resource/Rock/shadow/shadow.png";

RockShadowPtr RockShadow::getTask( ) {
	return  std::dynamic_pointer_cast< RockShadow >( Application::getInstance( )->getTask( getTag( ) ) );
}

RockShadow::RockShadow( ) :
_set_num( 0 ) {
	for ( int i = 0; i < MAX_SHADOW_NUM; i++ ) {
		_models[ i ] = ModelMDLPtr( new ModelMDL );
		_models[ i ]->setTexture( GRAPH_PATH.c_str( ) );
		_models[ i ]->setTrans( true );
	}
}


RockShadow::~RockShadow( ) {
}

void RockShadow::update( ) {
}

void RockShadow::reset( ) {
	_set_num = 0;
}

void RockShadow::set( const Vector& pos, const double scale ) {
	if ( _set_num >= MAX_SHADOW_NUM ) {
		return;
	}
	ModelMDLPtr shadow = _models[ _set_num ];
	shadow->reset( );
	createShadow( shadow, pos, scale );
	_set_num++;
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

int RockShadow::getSetNum( ) const {
	return _set_num;
}

ModelMDLPtr RockShadow::getModel( int idx ) const {
	return _models[ idx ];
}

Vector RockShadow::getAdjustPos( const Vector& pos ) {
	Vector result = pos;
	std::vector< ModelMV1Ptr > col_models = RockMap::getTask( )->getColModels( );
	int size = ( int )col_models.size( );
	for ( int i = 0; i < size; i++ ) {
		Vector fpos = result + Vector( 0, FALL_POWER, 0 );
		if ( col_models[ i ]->isHitLine( result, fpos ) ) {
			result.y = col_models[ i ]->getHitPos( ).y;
		}
	}
	return result;
}
