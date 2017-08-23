#include "ShotPlayer.h"
#include "SynchronousData.h"

static const int VANISH_LENGTH = 500;

ShotPlayer::ShotPlayer( const Vector& pos, DIR dir, int power ) :
Shot( pos, dir, power ) {
}

ShotPlayer::~ShotPlayer( ) {
}

void ShotPlayer::act( ) {
	if ( getActCount( ) * getVec( ).getLength( ) > VANISH_LENGTH ) {
		setFinished( );
	}
}

void ShotPlayer::setSynchronousData( unsigned char type, int camera_pos ) const {
	int ANIM[ ] = { 16, 17, 18, 19, 20, 21, 22, 23 };
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
	data->addObject( area, type, ANIM[ ( getPower( ) - 1 ) * 2 + ( getActCount( ) % 2 ) ], attribute, x, y );
}
