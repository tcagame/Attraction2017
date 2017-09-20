#include "EnemyBlueMonk.h"
#include "SynchronousData.h"
#include "Property.h"

const int WAIT_ANIM_TIME = 5;
const int MOVE_SPEED = 2;

EnemyBlueMonk::EnemyBlueMonk( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE ),
_before_pos( Vector( ) ),
_vec( Vector( MOVE_SPEED, 0 ) ) {
	PropertyPtr property( Property::getTask( ) );
	setPower( property->getData( "BlueMonk_POWER" ) );
	setForce( property->getData( "BlueMonk_FORCE" ) );
	setOverlappedRadius( property->getData( "Archer_RADIUS" ) );
}


EnemyBlueMonk::~EnemyBlueMonk( ) {
}

void EnemyBlueMonk::act( ) {
	if ( _before_pos.x == getPos( ).x ) {
		_vec.x *= -1;
		setVec( _vec );
	}
	_before_pos = getPos( );
}

void EnemyBlueMonk::setSynchronousData( int camera_pos ) const {
	const int ANIM[ ] = {
		220, 221, 222, 223, 224, 225, 226
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
