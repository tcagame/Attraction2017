#include "EnemyNoNeckGhost.h"
#include "SynchronousData.h"
#include "Property.h"

const int WAIT_ANIM_TIME = 5;
const int MOVE_SPEED = -4;
const int FLOAT_RANGE = 5;

EnemyNoNeckGhost::EnemyNoNeckGhost( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, false ),
_vy( 0 ),
_dir( 1 ) {
	PropertyPtr property( Property::getTask( ) );
	setPower( property->getData( "NoNeckGhost_POWER" ) );
	setForce( property->getData( "NoNeckGhost_FORCE" ) );
	setOverlappedRadius( property->getData( "NoNeckGhost_RADIUS" ) );
}


EnemyNoNeckGhost::~EnemyNoNeckGhost( ) {
}

void EnemyNoNeckGhost::act( ) {
	_vy += _dir;
	setVec( Vector( MOVE_SPEED, _vy ) );

	if ( _vy < -FLOAT_RANGE ) {
		_dir = 1;
	}
	if ( _vy > FLOAT_RANGE ) {
		_dir = -1;
	}
}

void EnemyNoNeckGhost::setSynchronousData( int camera_pos ) const {
	const int ANIM[ ] = {
		240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253
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
