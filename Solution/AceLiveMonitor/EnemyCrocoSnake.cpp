#include "EnemyCrocoSnake.h"
#include "SynchronousData.h"

static const int WAIT_ANIM_TIME = 5;
static const int MOVE_SPEED = -1;
static const int MAX_HP = 3;

EnemyCrocoSnake::EnemyCrocoSnake( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP ),
_before_pos( Vector( ) ) {
	setRadius( 30 );
	setVec( Vector( MOVE_SPEED, 0 ) );
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

void EnemyCrocoSnake::setSynchronousData( unsigned char type, int camera_pos ) const {
	const int ANIM[ ] = {
		160, 161, 162, 163, 164, 165, 164, 163, 162, 161
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	
	Vector pos = getPos( );
	int x = ( int )pos.x;
	int y = ( int )pos.y;

	AREA area = AREA_EVENT;
	if ( getState( ) == STATE_STREET ) {
		x -= camera_pos;
		area = AREA_STREET;
	}
	unsigned char attribute = 0;
	if ( getDir( ) == DIR_RIGHT ) {
		attribute |= SynchronousData::ATTRIBUTE_REVERSE;
	}
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->addObject( area, type, ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ], attribute, x, y );
}
