#include "EnemyRay.h"
#include "SynchronousData.h"
#include "Property.h"

const int WAIT_ANIM_TIME = 5;
const int GRAPH_WIDTH_NUM = 10;

EnemyRay::EnemyRay( const Vector& pos ) :
Enemy( pos, BIG_CHAR_GRAPH_SIZE, false ) {
	setOverlappedRadius( 18 );

	PropertyPtr property( Property::getTask( ) );
	setPower( property->getData( "Ray_POWER" ) );
	setForce( property->getData( "Ray_FORCE" ) );
}

EnemyRay::~EnemyRay( ) {
}

void EnemyRay::act( ) {
	Vector move( -3, 0 );
	setVec( move );
}

void EnemyRay::setSynchronousData( int camera_pos ) const {
	const int ANIM[ ] = {
		80, 81, 82, 83, 84, 85
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