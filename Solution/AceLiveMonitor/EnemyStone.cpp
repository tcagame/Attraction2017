#include "EnemyStone.h"
#include "SynchronousData.h"
#include "Property.h"

const int WAIT_ANIM_TIME = 2;
const int MOVE_SPEED = 5;


EnemyStone::EnemyStone( const Vector& pos ) :
Enemy( pos, SMALL_CHAR_GRAPH_SIZE ),
_before_pos( Vector( ) ),
_vec( Vector( -MOVE_SPEED, 2 ) ) {
	setVec( _vec );

	PropertyPtr property( Property::getTask( ) );
	setPower( property->getData( "Stone_POWER" ) );
	setForce( property->getData( "Stone_FORCE" ) );
	setOverlappedRadius( property->getData( "Stone_RADIUS" ) );
}


EnemyStone::~EnemyStone( ) {
}

void EnemyStone::act( ) {
	if ( _before_pos.x == getPos( ).x ) {
		_vec.x *= -1;
		setVec( _vec );
	}
	_before_pos = getPos( );
}

void EnemyStone::setSynchronousData( int camera_pos ) const {
	const int ANIM[ ] = {
		56, 57, 58, 59
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


void EnemyStone::damage( int force ) {
}