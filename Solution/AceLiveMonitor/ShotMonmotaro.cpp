#include "ShotMonmotaro.h"
#include "SynchronousData.h"

static const int SHOT_SPEED = 10;
static const int MAX_HEIGHT = 5;
static const int WAVE_COUNT = 30;
static const int VANISH_LENGTH = 320;

ShotMonmotaro::ShotMonmotaro( const PLAYER player, const Vector& pos, DIR dir, int power ) :
Shot( pos, power ) {
	Vector vec( SHOT_SPEED, 0 );
	if ( dir == DIR_LEFT ) {
		vec.x *= -1;
	}
	setVec( vec );
}

ShotMonmotaro::~ShotMonmotaro( ) {
}

void ShotMonmotaro::act( ) {
	Vector vec( getVec( ) );
	vec.y = sin( PI2 / WAVE_COUNT * getActCount( ) ) * ( MAX_HEIGHT / 2 );
	setVec( vec );

	double check_vec = getVec( ).x;
	if ( getActCount( ) * check_vec > VANISH_LENGTH ) {
		setFinished( );
	}
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
	if ( getVec( ).x >= 0 ) {
		attribute |= SynchronousData::ATTRIBUTE_REVERSE;
	}
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->addObject( area, type, ANIM[ getActCount( ) % anim_size ], attribute, x, y );
}
