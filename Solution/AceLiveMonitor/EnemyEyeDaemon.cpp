#include "EnemyEyeDaemon.h"
#include "SynchronousData.h"

static const int WAIT_ANIM_TIME = 5;
static const int MAX_HP = 2;
const int MOVE_SPEED = 1;
const int JUMP_COUNT = 6;

EnemyEyeDaemon::EnemyEyeDaemon( const Vector& pos ) :
Enemy( pos, SMALL_CHAR_GRAPH_SIZE, MAX_HP ),
_before_pos( pos ),
_air_jump( false ) {
	setRadius( 16 );
}


EnemyEyeDaemon::~EnemyEyeDaemon( ) {
}

void EnemyEyeDaemon::act( ) {
	if ( _before_pos.x == getPos( ).x ) {
		if ( getDir( ) == DIR_LEFT ) {
			setVec( Vector( MOVE_SPEED, 0 ) );
		} else {
			setVec( Vector( -MOVE_SPEED, 0 ) );
		}
	}
	if ( getActCount( ) % JUMP_COUNT == 0 && isStanding( ) ) {
		Vector vec = getVec( );
		vec.y -= 12;
		setVec( vec );
	}
	if ( !_air_jump && getVec( ).y > 0 ) {
		_air_jump = true;
		Vector vec( getVec( ) );
		vec.y -= 12;
		setVec( vec );
	}
	if ( isStanding( ) ) {
		_air_jump = false;
	}

	_before_pos = getPos( );
}

void EnemyEyeDaemon::setSynchronousData( unsigned char type, int camera_pos ) const {
	const int ANIM[ ] = {
		48, 49, 50, 51, 52, 53, 54, 55
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