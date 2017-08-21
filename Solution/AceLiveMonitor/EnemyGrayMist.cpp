#include "EnemyGrayMist.h"
#include "SynchronousData.h"

static const int WAIT_ANIM_TIME = 5;
static const int MOVE_SPEED = 1;
static const int FLOAT_RANGE = 6;
static const int MAX_HP = 3;

EnemyGrayMist::EnemyGrayMist( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP, false ),
_vy( 0 ),
_dir( 1 ) {
	setRadius( 36 );
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

void EnemyGrayMist::setSynchronousData( unsigned char type, int camera_pos ) const {
	const int ANIM[ ] = {
		151, 152, 153, 154, 155, 156, 155, 154, 153, 152
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