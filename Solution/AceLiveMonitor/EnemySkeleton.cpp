#include "EnemySkeleton.h"
#include "SynchronousData.h"
#include "Property.h"

const int WAIT_ANIM_TIME = 5;
const int GRAPH_WIDTH_NUM = 10;

EnemySkeleton::EnemySkeleton( const Vector& pos ) :
Enemy( pos, BIG_CHAR_GRAPH_SIZE, false ) {
	setOverlappedRadius( 18 );

	PropertyPtr property( Property::getTask( ) );
	setPower( property->getData( "Skeleton_POWER" ) );
	setForce( property->getData( "Skeleton_FORCE" ) );
}

EnemySkeleton::~EnemySkeleton( ) {
}

void EnemySkeleton::act( ) {
	Vector move( -3, 0 );
	setVec( move );
}

void EnemySkeleton::setSynchronousData( int camera_pos ) const {
	const int ANIM[ ] = {
		96, 97, 98, 99, 100, 101, 102, 103, 104, 105
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
	unsigned char type = getType( );
	data->addObject( area, type, ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ], attribute, x, y );
}