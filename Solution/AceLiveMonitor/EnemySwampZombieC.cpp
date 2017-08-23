#include "EnemySwampZombieC.h"
#include "SynchronousData.h"

static const int WAIT_ANIM_TIME = 5;
static const int MAX_HP = 3;

EnemySwampZombieC::EnemySwampZombieC( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP ) {
	setRadius( 36 );
}


EnemySwampZombieC::~EnemySwampZombieC( ) {
}

void EnemySwampZombieC::act( ) {

}

void EnemySwampZombieC::setSynchronousData( unsigned char type, int camera_pos ) const {
	const int ANIM[ ] = {
		100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115
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


void EnemySwampZombieC::damage( int force ) {
}