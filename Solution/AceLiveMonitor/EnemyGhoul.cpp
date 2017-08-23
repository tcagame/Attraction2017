#include "EnemyGhoul.h"
#include "SynchronousData.h"

const int WAIT_ANIM_TIME = 5;
const int MAX_HP = 3;
const int MOVE_SPEED = 1;
const int MOVE_RANGE = 25;

EnemyGhoul::EnemyGhoul( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP ),
_origin_pos( pos ) {
	setVec( Vector( MOVE_SPEED, 0 ) );
}


EnemyGhoul::~EnemyGhoul( ) {
}

void EnemyGhoul::act( ) {
	Vector vec = getVec( );
	Vector diff = getPos( ) - _origin_pos;
	if ( diff.getLength( ) > MOVE_RANGE ) {
		if ( getDir( ) == DIR_RIGHT ) {
			vec.x *= -1;
			setVec( vec );
		}
		if ( getDir( ) == DIR_LEFT ) {
			vec.x *= -1;
			setVec( vec );
		}
	}
}

void EnemyGhoul::setSynchronousData( unsigned char type, int camera_pos ) const {
	const int ANIM[ ] = {
		20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
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
	data->addObject( area, type, ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ], attribute, x, y );
}
