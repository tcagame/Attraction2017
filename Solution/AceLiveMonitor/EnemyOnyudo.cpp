#include "EnemyOnyudo.h"
#include "SynchronousData.h"
#include "Property.h"

const int WAIT_ANIM_TIME = 5;
const int GRAPH_WIDTH_NUM = 16;
const int MOVE_SPEED = 1;

EnemyOnyudo::EnemyOnyudo( const Vector& pos ) :
Enemy( pos, BIG_CHAR_GRAPH_SIZE ),
_before_pos( Vector( ) ), 
_vec( MOVE_SPEED, 0 ) {
	PropertyPtr property( Property::getTask( ) );
	setPower( property->getData( "Onyudo_POWER" ) );
	setForce( property->getData( "Onyudo_FORCE" ) );
	setOverlappedRadius( property->getData( "Onyudo_RADIUS" ) );
}


EnemyOnyudo::~EnemyOnyudo( ) {
}

void EnemyOnyudo::act( ) {
	if ( _before_pos.x == getPos( ).x ) {
		_vec.x *= -1;
		setVec( _vec );
	}
	_before_pos = getPos( );
}

void EnemyOnyudo::setSynchronousData( int camera_pos ) const {
	const int ANIM[ ] = {
		16, 17, 18, 19, 20, 21, 22, 23
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
