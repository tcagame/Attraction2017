#include "ShotPlayer.h"
#include "SynchronousData.h"
#include "Armoury.h"
#include "ShotReflect.h"
#include "Family.h"
#include "Player.h"

const int SHOT_SPEED = 15;
const int VANISH_LENGTH = 320;

ShotPlayer::ShotPlayer( const PLAYER player, const Vector& pos, DIR dir, int level, bool normal ) :
Shot( pos, ( int )( pow( 2, level - 1 ) + 1 ) ),
_level( level ), 
_normal( normal ),
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
	ShotPtr shot = ShotPtr( new ShotReflect( _player, getPos( ) ) );
	shot->setArea( getArea( ) );
	Armoury::getTask( )->add( shot );
	Shot::erase( );
}

void ShotPlayer::setSynchronousData( int camera_pos ) const {
	int ANIM[ ] = { 16, 17, 18, 19, 20, 21, 22, 23, 14, 15 };
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
	data->addObject( area, SynchronousData::TYPE_SHOT, ANIM[ ( _level - 1 ) * 2 + ( getActCount( ) % 2 ) ], attribute, x, y );
}

bool ShotPlayer::isNormal( ) {
	return _normal;
}
