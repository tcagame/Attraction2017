#include "EnemySwampZombieA.h"
#include "SynchronousData.h"

static const int WAIT_ANIM_TIME = 5;
static const int MAX_HP = 3;

EnemySwampZombieA::EnemySwampZombieA( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP ) {
	setRadius( 36 );
}


EnemySwampZombieA::~EnemySwampZombieA( ) {
}

void EnemySwampZombieA::act( ) {

}

void EnemySwampZombieA::setSynchronousData( unsigned char type, int camera_pos ) const {
	const int ANIM[ ] = {
		120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133
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

void EnemySwampZombieA::damage( int force ) {
}

