#include "RockMapStreetCamera.h"
#include "Application.h"
#include "Drawer.h"
#include "RockFamily.h"
#include "RockPlayer.h"

const Vector INIT_POS = Vector( 0, 500, -1000 );
const Vector INIT_TARGET = Vector( 0, 60, -500 );


RockMapStreetCamera::RockMapStreetCamera( ) :
RockCamera( INIT_POS, INIT_TARGET ) {
	_dir[ RockMapStreet::STAGE_STREET ] = Vector( 0, 0.8, -1 );
	_dir[ RockMapStreet::STAGE_CAVE   ] = Vector( 0, 0.8, -1 );
	_dir[ RockMapStreet::STAGE_RYUGU  ] = Vector( 1, 0.25,  0 );
	
	_length[ RockMapStreet::STAGE_STREET ] = 300.0;
	_length[ RockMapStreet::STAGE_CAVE   ] = 300.0;
	_length[ RockMapStreet::STAGE_RYUGU  ] = 250.0;
}


RockMapStreetCamera::~RockMapStreetCamera( ) {
}

void RockMapStreetCamera::setCamera( ) {
	RockMapStreetPtr map = std::dynamic_pointer_cast< RockMapStreet >( RockMap::getTask( ) );
	Vector target = RockFamily::getTask( )->getCameraPos( );
	if ( target.isOrijin( ) ) {
		setPos( INIT_POS );
		setTarget( INIT_TARGET );
	} else {
		RockMapStreet::STAGE stage = map->getStage( );
		Vector pos = target + _dir[ stage ] * _length[ stage ];
		setPos( pos );
		setTarget( target );
	}
}
