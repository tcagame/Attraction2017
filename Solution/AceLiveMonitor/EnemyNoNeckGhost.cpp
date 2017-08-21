#include "EnemyNoNeckGhost.h"
#include "SynchronousData.h"

const int WAIT_ANIM_TIME = 5;
const int MAX_HP = 3;
const int MOVE_SPEED = -4;
const int FLOAT_RANGE = 5;

EnemyNoNeckGhost::EnemyNoNeckGhost( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP, false ),
_vy( 0 ),
_dir( 1 ) {
	setRadius( 36 );
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

void EnemyNoNeckGhost::setSynchronousData( unsigned char type, int camera_pos ) const {
	const int ANIM[ ] = {
		200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	
	Vector pos = getPos( );
	int x = ( int )pos.x;
	int y = ( int )pos.y;

	AREA area = AREA_EVENT;
	if ( getState( ) == STATE_MAIN ) {
		x -= camera_pos;
		area = AREA_MAIN;
	}
	unsigned char attribute = 0;
	if ( getDir( ) == DIR_RIGHT ) {
		attribute |= SynchronousData::ATTRIBUTE_REVERSE;
	}
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->addObject( area, type, ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ], attribute, x, y );
}
