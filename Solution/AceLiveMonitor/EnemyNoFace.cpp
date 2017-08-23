#include "EnemyNoFace.h"
#include "ace_define.h"
#include "SynchronousData.h"

const int WAIT_ANIM_TIME = 5;
const int MAX_HP = 3;
const int MOVE_RANGE = 10;
const double MOVE_SPEED = 0.5;

EnemyNoFace::EnemyNoFace( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP ),
_vec_x( -MOVE_SPEED ) {
	setRadius( 36 );
	setVec( Vector( _vec_x, 0 ) );
}

EnemyNoFace::~EnemyNoFace( ) {
}

void EnemyNoFace::act( ) {
	Vector vec = getVec( );

	if ( vec.x < -MOVE_RANGE ) {
		_vec_x = MOVE_SPEED;
	}
	if ( vec.x > MOVE_RANGE ) {
		_vec_x = -MOVE_SPEED;
	}

	setVec( Vector( vec.x + _vec_x, vec.y ) );
}

void EnemyNoFace::setSynchronousData( unsigned char type, int camera_pos ) const {
	const int ANIM[ ] = {
		220, 221, 222, 223, 224, 225, 226, 227, 226, 227, 226, 225, 224, 223, 222, 221
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