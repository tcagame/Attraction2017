#include "EnemyGreenZombie.h"
#include "SynchronousData.h"

static const int WAIT_ANIM_TIME = 5;
static const int MOVE_SPEED = -5;
static const int JUMP_POWER = -10;
static const int MAX_HP = 3;

EnemyGreenZombie::EnemyGreenZombie( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP ),
_before_pos( Vector( ) ) {
	setVec( Vector( MOVE_SPEED, 0 ) );
	setRadius( 36 );
}


EnemyGreenZombie::~EnemyGreenZombie( ) {
}

void EnemyGreenZombie::act( ) {
	if ( _before_pos.x == getPos( ).x ) {
		Vector vec( getVec( ) );
		vec.x *= -1;
		setVec( vec );
	}
	if ( isStanding( ) && getActCount( ) % 30 == 0 ) {
		Vector vec( getVec( ) );
		vec.y = JUMP_POWER;
		setVec( vec );
	}
	_before_pos = getPos( );
}

void EnemyGreenZombie::setSynchronousData( unsigned char type, int camera_pos ) const {
	const int ANIM[ ] = {
		66, 67, 68, 69, 70, 71
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

Chip EnemyGreenZombie::getChip( ) const {
	return Chip( );
}
