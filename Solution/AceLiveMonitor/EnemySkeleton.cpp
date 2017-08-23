#include "EnemySkeleton.h"
#include "SynchronousData.h"

static const int WAIT_ANIM_TIME = 5;
static const int GRAPH_WIDTH_NUM = 10;
static const int MAX_HP = 6;

EnemySkeleton::EnemySkeleton( const Vector& pos ) :
Enemy( pos, BIG_CHAR_GRAPH_SIZE, MAX_HP, false ) {
	setRadius( 18 );
}

EnemySkeleton::~EnemySkeleton( ) {
}

void EnemySkeleton::act( ) {
	Vector move( -3, 0 );
	setVec( move );
}

void EnemySkeleton::setSynchronousData( unsigned char type, int camera_pos ) const {
	const int ANIM[ ] = {
		50, 51, 52, 53, 54, 55, 56, 57, 58, 59
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