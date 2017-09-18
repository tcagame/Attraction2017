#include "EnemyOneEyeSnake.h"
#include "SynchronousData.h"
#include "Property.h"

const int WAIT_ANIM_TIME = 5;
const int MOVE_SPEED = 2;
const int JUMP_POWER = -400;

EnemyOneEyeSnake::EnemyOneEyeSnake( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE ),
_before_pos( Vector( ) ),
_vec( Vector( MOVE_SPEED, 0 ) ) {
	setOverlappedRadius( 36 );

	PropertyPtr property( Property::getTask( ) );
	setPower( property->getData( "OneEyeSnake_POWER" ) );
	setForce( property->getData( "OneEyeSnake_FORCE" ) );
}


EnemyOneEyeSnake::~EnemyOneEyeSnake( ) {
}

void EnemyOneEyeSnake::act( ) {
	if ( _before_pos.x == getPos( ).x ) {
		_vec.x *= -1;
		setVec( _vec );
	}
	if ( isStanding( ) && getActCount( ) % 90 == 0 ) {
		_vec.y += JUMP_POWER;
		setVec( _vec );
	}
	_before_pos = getPos( );
}

void EnemyOneEyeSnake::setSynchronousData( int camera_pos ) const {
	const int ANIM[ ] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 10
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