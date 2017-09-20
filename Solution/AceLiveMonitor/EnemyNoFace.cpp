#include "EnemyNoFace.h"
#include "ace_define.h"
#include "SynchronousData.h"
#include "Property.h"

const int WAIT_ANIM_TIME = 4;
const int REVERSE_TIME = 100;
const double MOVE_SPEED = 0.5;

EnemyNoFace::EnemyNoFace( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE ),
_accel_x( -MOVE_SPEED ) {
	setVec( Vector( _accel_x, 0 ) );

	PropertyPtr property( Property::getTask( ) );
	setPower( property->getData( "NoFace_POWER" ) );
	setForce( property->getData( "NoFace_FORCE" ) );
	setOverlappedRadius( property->getData( "NoFace_RADIUS" ) );
}

EnemyNoFace::~EnemyNoFace( ) {
}

void EnemyNoFace::act( ) {
	Vector vec = getVec( );
	if ( getActCount( ) % REVERSE_TIME == 0 ) {
		_accel_x *= -1;
	}

	setVec( Vector( vec.x + _accel_x, vec.y ) );
}

void EnemyNoFace::setSynchronousData( int camera_pos ) const {
	const int ANIM[ ] = {
		260, 261, 262, 263, 264, 265, 266, 267, 268, 269
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	
	Vector pos = getPos( );
	int x = ( int )pos.x;
	int y = ( int )pos.y;

	AREA area = AREA_EVENT;
	if ( getArea( ) == AREA_STREET ) {
		x -= camera_pos;
		area = AREA_STREET;
	}
	unsigned char attribute = 0;
	if ( getDir( ) == DIR_RIGHT ) {
		attribute |= SynchronousData::ATTRIBUTE_REVERSE;
	}
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	unsigned char type = getType( );
	data->addObject( area, type, ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ], attribute, x, y );
}