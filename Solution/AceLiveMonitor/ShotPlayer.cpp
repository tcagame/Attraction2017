#include "ShotPlayer.h"
#include "SynchronousData.h"
#include "Armoury.h"
#include "ShotReflect.h"

static const int SHOT_SPEED = 15;
static const int VANISH_LENGTH = 320;

ShotPlayer::ShotPlayer( const PLAYER player, const Vector& pos, DIR dir, int power ) :
Shot( pos, power ),
_player( player ) {
	Vector vec = Vector( SHOT_SPEED, 0 );
	if ( dir == DIR_LEFT ) {
		vec.x *= -1;
	}
	setVec( vec );
}

ShotPlayer::~ShotPlayer( ) {
}

void ShotPlayer::act( ) {
	if ( getActCount( ) * getVec( ).getLength( ) > VANISH_LENGTH ) {
		erase( );
	}
}

void ShotPlayer::erase( ) {
	// ’µ‚Ë•Ô‚è’e‚ð¶¬
	Armoury::getTask( )->add( ShotPtr( new ShotReflect( _player, getPos( ) ) ) );
	setFinished( );
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
	if ( getVec( ).x >= 0 ) {
		attribute |= SynchronousData::ATTRIBUTE_REVERSE;
	}
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->addObject( area, type, ANIM[ ( getPower( ) - 1 ) * 2 + ( getActCount( ) % 2 ) ], attribute, x, y );
}
