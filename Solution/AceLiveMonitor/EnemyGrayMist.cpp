#include "EnemyGrayMist.h"
#include "SynchronousData.h"
#include "Property.h"

const int WAIT_ANIM_TIME = 5;
const int MOVE_SPEED = 1;
const int FLOAT_RANGE = 6;

EnemyGrayMist::EnemyGrayMist( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, false ),
_vy( 0 ),
_dir( 1 ) {
	setOverlappedRadius( 30 );
	if ( getPos( ).y > GRAPH_SIZE / 3 * 2 ) {
		setPos( Vector( getPos( ).x, GRAPH_SIZE / 3 * 2 ) );
	}

	PropertyPtr property( Property::getTask( ) );
	setPower( property->getData( "GrayMist_POWER" ) );
	setForce( property->getData( "GrayMist_FORCE" ) );
	setOverlappedRadius( property->getData( "GrayMist_RADIUS" ) );
}


EnemyGrayMist::~EnemyGrayMist( ) {
}

void EnemyGrayMist::act( ) {
	Vector move_speed( -MOVE_SPEED, _vy );
	_vy += _dir;
	setVec( move_speed );

	if ( _vy < -FLOAT_RANGE ) {
		_dir = 1;
	}
	if ( _vy > FLOAT_RANGE ) {
		_dir = -1;
	}
}

void EnemyGrayMist::setSynchronousData( int camera_pos ) const {
	const int ANIM[ ] = {
		170, 171, 172, 173, 174, 175, 176, 177, 178, 179
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