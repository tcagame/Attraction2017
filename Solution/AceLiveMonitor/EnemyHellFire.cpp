#include "EnemyHellFire.h"
#include "Family.h"
#include "SynchronousData.h"

static const int HP = 3;
static const double MOVE_SPEED = 3;
static const double ACCEL = 0.5;
static const int WAIT_ANIM_TIME = 5;

EnemyHellFire::EnemyHellFire( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, HP, false ) {
	setVec( Vector( MOVE_SPEED, 0 ) );
}


EnemyHellFire::~EnemyHellFire( ) {
}

void EnemyHellFire::act( ) {
	Vector target = Vector( Family::getTask( )->getCameraPos( ) + GRAPH_SIZE, GRAPH_SIZE / 2 );
	Vector distance = target - getPos( );
	Vector vec = getVec( ) + distance.normalize( ) * ACCEL;
	vec = vec.normalize( ) * MOVE_SPEED;
	setVec( vec );
}

void EnemyHellFire::setSynchronousData( unsigned char type, int camera_pos ) const {
	const int ANIM[ ] = {
		320, 321, 322, 323, 324, 325, 326, 327, 328, 329,
		330, 331, 332, 333, 334, 335, 336, 337, 338, 339,
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
