#include "EnemyCrocoSnake.h"
#include "SynchronousData.h"
#include "Property.h"

const int WAIT_ANIM_TIME = 5;
const int MOVE_SPEED = -1;

EnemyCrocoSnake::EnemyCrocoSnake( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE ),
_before_pos( Vector( ) ) {
	setVec( Vector( MOVE_SPEED, 0 ) );

	PropertyPtr property( Property::getTask( ) );
	setPower( property->getData( "CrocoSnake_POWER" ) );
	setForce( property->getData( "CrocoSnake_FORCE" ) );
	setOverlappedRadius( property->getData( "CrocoSnake_RADIUS" ) );
}


EnemyCrocoSnake::~EnemyCrocoSnake( ) {
}

void EnemyCrocoSnake::act( ) {
	if ( _before_pos.x == getPos( ).x ) {
		if ( getDir( ) == DIR_LEFT ) {
			setVec( Vector( MOVE_SPEED, 0 ) );
		} else {
			setVec( Vector( -MOVE_SPEED, 0 ) );
		}
	}
	_before_pos = getPos( );
}

void EnemyCrocoSnake::setSynchronousData( int camera_pos ) const {
	const int ANIM[ ] = {
		180, 181, 182, 183, 184, 185, 186, 187, 188

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
