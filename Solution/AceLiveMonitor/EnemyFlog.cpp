#include "EnemyFlog.h"
#include "SynchronousData.h"

const int WAIT_ANIM_TIME = 5;
const int JUMP_TIME = WAIT_ANIM_TIME * 6;
const int MAX_HP = 2;
const int JUMP_POWER = -5;
const int MOVE_SPEED = 2;

EnemyFlog::EnemyFlog( const Vector& pos ) :
Enemy( pos, SMALL_CHAR_GRAPH_SIZE, MAX_HP ) {
	setRadius( 16 );
}


EnemyFlog::~EnemyFlog( ) {
}

void EnemyFlog::act( ) {
	if ( isStanding( ) ) {
		setVec( Vector( ) );
	}
	if ( isStanding( ) && !( ( getActCount( ) + WAIT_ANIM_TIME * 3 ) % JUMP_TIME ) ) {
		if ( rand( ) % 2 ) {
			setVec( Vector( MOVE_SPEED, JUMP_POWER ) );
		} else {
			setVec( Vector( -MOVE_SPEED, JUMP_POWER ) );
		}
	}
}

void EnemyFlog::setSynchronousData( unsigned char type, int camera_pos ) const {
	const int ANIM[ ] = {
		24, 25, 26, 27, 28, 29
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