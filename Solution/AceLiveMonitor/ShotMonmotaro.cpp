#include "ShotMonmotaro.h"
#include "SynchronousData.h"

ShotMonmotaro::ShotMonmotaro( const Vector& pos, DIR dir, int power ) :
Shot( pos, dir, power ) {
}

ShotMonmotaro::~ShotMonmotaro( ) {
}

void ShotMonmotaro::act( ) {
}

void ShotMonmotaro::setSynchronousData( unsigned char type, int camera_pos ) const {
	int ANIM[ ] = { 24 };
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
	data->addObject( area, type, ANIM[ getActCount( ) % anim_size ], attribute, x, y );
}
