#include "RockMapStreetCamera.h"
#include "Application.h"
#include "Drawer.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockMapStreet.h"


const Vector INIT_POS = Vector( 0, 500, -1000 );
const Vector INIT_TARGET = Vector( 0, 60, -500 );

const Vector STREET_DIR = Vector( 0, 0.8, -1 ).normalize( );
const Vector BOSS_DIR = Vector( -1, 0.5, 0 ).normalize( );
const double LENGTH = 300;


RockMapStreetCamera::RockMapStreetCamera( ) :
RockCamera( INIT_POS, INIT_TARGET ) {
	_dir[ RockMapStreet::STAGE_STREET ] = Vector( 0, 0.8, -1 );
	_dir[ RockMapStreet::STAGE_CAVE   ] = Vector( -1, 0.8, -1 );
	_dir[ RockMapStreet::STAGE_RYUGU  ] = Vector( 1, 0.25,  0 );
	
	_length[ RockMapStreet::STAGE_STREET ] = 300.0;
	_length[ RockMapStreet::STAGE_CAVE   ] = 300.0;
	_length[ RockMapStreet::STAGE_RYUGU  ] = 250.0;
}


RockMapStreetCamera::~RockMapStreetCamera( ) {
}

void RockMapStreetCamera::setCamera( ) {
	Vector target = RockFamily::getTask( )->getCameraPos( );
	RockMapStreetPtr map = std::dynamic_pointer_cast< RockMapStreet >( RockMap::getTask( ) );
	RockMapStreet::STAGE stage = map->getStage( );

	if ( target.isOrijin( ) ) {
		setPos( INIT_POS );
		setTarget( INIT_TARGET );
	} else {
		Vector pos;
		switch( stage ) {
		case RockMapStreet::STAGE_STREET:
			pos = target + _dir[ stage ] * _length[ stage ];
			break;
		case RockMapStreet::STAGE_CAVE:
			pos = target +_dir[ stage ] * _length[ stage ];
			break;
		case RockMapStreet::STAGE_RYUGU:
			RockMapStreet::STAGE stage = map->getStage( );
			pos = target + _dir[ stage ] * _length[ stage ];
			if ( pos.x > 1000 ) {
				pos.x = 1000;
				target = pos - _dir[ stage ] * _length[ stage ];
			}
			break;
		}
		setPos( pos );
		setTarget( target );
	}
}
