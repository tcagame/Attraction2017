#include "EnemyLady.h"
#include "SynchronousData.h"
#include "Property.h"

const int WAIT_ANIM_TIME = 5;
const int GRAPH_WIDTH_NUM = 10;

EnemyLady::EnemyLady( const Vector& pos ) :
Enemy( pos, BIG_CHAR_GRAPH_SIZE, false ) {
	PropertyPtr property( Property::getTask( ) );
	setPower( property->getData( "Lady_POWER" ) );
	setForce( property->getData( "Lady_FORCE" ) );
	setOverlappedRadius( property->getData( "Lady_RADIUS" ) );
}


EnemyLady::~EnemyLady( ) {
}

void EnemyLady::act( ) {
	Vector move( -3, 0 );
	setVec( move );
}

void EnemyLady::setSynchronousData( int camera_pos ) const {
	const int ANIM[ ] = {
		86, 87, 88, 89, 90
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

Vector EnemyLady::getOverlappedPos( ) const {
	return getPos( ) + Vector( -35, -65 );
}