#include "Monmotaro.h"
#include "SynchronousData.h"
#include "Family.h"

static const int MOVE_SPEED = 3;
static const int WAIT_ANIM_TIME = 3;
static const int MOVE_IN_TIME = WAIT_ANIM_TIME * 8;

Monmotaro::Monmotaro( const Vector& pos, const Vector& target ) :
Character( pos, NORMAL_CHAR_GRAPH_SIZE, 1, false ),
_action( ACTION_FADE_IN ),
_target( target ) {
	Vector vec = ( target - pos ).normalize( ) * MOVE_SPEED;
	setVec( vec );
}

Monmotaro::~Monmotaro( ) {
}

void Monmotaro::act( ) {
	switch ( _action ) {
	case ACTION_FADE_IN:
		{
			Vector vec = ( _target - getPos( ) ).normalize( ) * MOVE_SPEED;
			setVec( vec );
			if ( ( getPos( ) - _target ).getLength2( ) < 1 ) {
				_action = ACTION_MOVE_IN;
				setActCount( 0 );
			}
		}
		break;
	case ACTION_MOVE_IN:
		if ( getActCount( ) > MOVE_IN_TIME ) {
			_action = ACTION_WAIT;
			setVec( Vector( ) );
		}
		break;
	case ACTION_WAIT:
		break;
	}
	setSynchronousData( );
}

void Monmotaro::damage( int force ) {
	if ( force < 0 ) {
		_action = ACTION_OUT;
	}
}

void Monmotaro::setTarget( const Vector& target ) {
	_target = target;
}

Monmotaro::ACTION Monmotaro::getAction( ) const {
	return _action;
}

void Monmotaro::setSynchronousData( ) {
	int camera_pos = ( int )Family::getTask( )->getCameraPos( );
	
	Vector pos = getPos( );
	int x = ( int )pos.x;
	int y = ( int )pos.y;

	AREA area = AREA_EVENT;
	if ( getState( ) == STATE_STREET ) {
		x -= camera_pos;
		area = AREA_STREET;
	}

	unsigned char type = SynchronousData::TYPE_MONMOTARO;
	int pattern = 0;
	switch ( _action ) {
	case ACTION_FADE_IN:
		{
			const int ANIM[ ] = { 0, 1, 2, 1 };
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			pattern = ANIM[ ( getActCount( ) / WAIT_ANIM_TIME ) % anim_num ];
		}
		break;
	case ACTION_MOVE_IN:
		{
			const int ANIM[ ] = { 16, 17, 18, 19, 20, 21, 22, 23 };
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			pattern = ANIM[ ( getActCount( ) / WAIT_ANIM_TIME ) % anim_num ];
		}
		break;
	case ACTION_WAIT:
		{
			const int ANIM[ ] = { 3, 4, 5, 6, 5, 4 };
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			pattern = ANIM[ ( getActCount( ) / WAIT_ANIM_TIME ) % anim_num ];
		}
		break;
	}
	unsigned char attribute = 0;
	if ( getDir( ) == DIR_RIGHT ) {
		attribute |= SynchronousData::ATTRIBUTE_REVERSE;
	}
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->addObject( area, type, pattern, attribute, x, y );
}
