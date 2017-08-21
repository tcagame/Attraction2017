#include "EnemyStone.h"
#include "SynchronousData.h"

static const int WAIT_ANIM_TIME = 5;
static const int MOVE_SPEED = 5;
static const int MAX_HP = 2;

EnemyStone::EnemyStone( const Vector& pos ) :
Enemy( pos, SMALL_CHAR_GRAPH_SIZE, MAX_HP ),
_before_pos( Vector( ) ),
_vec( Vector( -MOVE_SPEED, 2 ) ) {
	setRadius( 16 );
	setVec( _vec );
}


EnemyStone::~EnemyStone( ) {
}

void EnemyStone::act( ) {
	if ( _before_pos.x == getPos( ).x ) {
		_vec.x *= -1;
		setVec( _vec );
	}
	_before_pos = getPos( );
}

void EnemyStone::setSynchronousData( unsigned char type, int camera_pos ) const {
	const int ANIM[ ] = {
		48, 49, 50, 51, 52, 53, 54, 55
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


void EnemyStone::damage( int force ) {
}