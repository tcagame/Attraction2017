#include "ShotReflect.h"
#include "Family.h"
#include "Player.h"
#include "SynchronousData.h"

const double MOVE_SPEED = 10;
const double REACH_RANGE = 32;
const double WAVE_RANGE = 16;
const double CYCLE = 160;

ShotReflect::ShotReflect( PLAYER player, const Vector& pos ) :
Shot( pos, 0 ),
_player( player ) {
}


ShotReflect::~ShotReflect( ) {
}

void ShotReflect::setSynchronousData( unsigned char type, int camera_pos ) const {
	const int ANIM = 16;

	Vector pos = getPos( );
	int x = ( int )pos.x;
	int y = ( int )( pos.y + cos( PI * 2 * pos.x / CYCLE ) * WAVE_RANGE );

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
	data->addObject( area, type, ANIM, attribute, x, y );
}

void ShotReflect::act( ) {
	PlayerPtr target = Family::getTask( )->getPlayer( _player );
	if ( !target ->isExist( ) ) {
		erase( );
		return;
	}

	Vector vec = target->getPos( ) - getPos( );
	if ( vec.getLength( ) < REACH_RANGE ) {
		erase( );
		return;
	}


	vec = vec.normalize( ) * MOVE_SPEED;
	setVec( vec );
}