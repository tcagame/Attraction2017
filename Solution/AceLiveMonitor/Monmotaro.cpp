#include "Monmotaro.h"
#include "SynchronousData.h"
#include "Family.h"

//ë¨ìx
static const int ENTRY_SPEED = 3;
static const int MAX_SPEED = 18;
static const int MOVE_SPEED = 6;

//è¡Ç¶ÇÈéûä‘
static const int FADE_OUT_TIME = 30 * 60;

static const int WAIT_ANIM_TIME = 3;
static const int FADE_IN_OUT_TIME = WAIT_ANIM_TIME * 8;
static const Vector LEAVE_POS[ 2 ] {
	Vector(  32, -64 ),
	Vector( -32, -64 )
};

Monmotaro::Monmotaro( const Vector& pos, const Target& target ) :
Character( pos, NORMAL_CHAR_GRAPH_SIZE, 1, false ),
_action( ACTION_ENTRY ),
_target( target ) {
	Vector vec = ( target.pos - pos ).normalize( ) * ENTRY_SPEED;
	setVec( vec );
}

Monmotaro::~Monmotaro( ) {
}

void Monmotaro::act( ) {
	switch ( _action ) {
	case ACTION_ENTRY:
		{
			Vector vec = ( _target.pos - getPos( ) ).normalize( ) * ENTRY_SPEED;
			setVec( vec );
			if ( ( getPos( ) - _target.pos ).getLength( ) < 1 ) {
				setDir( _target.dir );
				setPos( _target.pos + LEAVE_POS[ _target.dir ] );
				_action = ACTION_FADE_IN;
				setVec( Vector( ) );
				setActCount( 0 );
			}
		}
		break;
	case ACTION_FADE_IN:
		if ( getActCount( ) > FADE_IN_OUT_TIME ) {
			_action = ACTION_MOVE;
			setVec( Vector( ) );
		}
		break;
	case ACTION_MOVE:
		{
			Vector target_pos = _target.pos + LEAVE_POS[ _target.dir ];
			Vector vec = ( target_pos - getPos( ) ).normalize( ) * MOVE_SPEED;
			if ( vec.getLength2( ) > MAX_SPEED * MAX_SPEED ) {
				vec = vec.normalize( ) * MAX_SPEED;
			}
			if ( vec.getLength2( ) > ( target_pos - getPos( ) ).getLength2( ) ) {
				vec = ( target_pos - getPos( ) );
			}
			setVec( vec );
			if ( getActCount( ) > FADE_OUT_TIME ) {
				_action = ACTION_FADE_OUT;
				setActCount( 0 );
			}
		}
		break;
	case ACTION_FADE_OUT:
		if ( getActCount( ) > FADE_IN_OUT_TIME ) {
			setFinished( );
		}
		break;
	}
	setSynchronousData( );
}

void Monmotaro::damage( int force ) {
	if ( force < 0 ) {
		_action = ACTION_FADE_OUT;
	}
}

void Monmotaro::setTarget( const Target& target ) {
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
	case ACTION_ENTRY:
		{
			const int ANIM[ ] = { 0, 1, 2, 1 };
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			pattern = ANIM[ ( getActCount( ) / WAIT_ANIM_TIME ) % anim_num ];
		}
		break;
	case ACTION_FADE_IN:
		{
			const int ANIM[ ] = { 16, 17, 18, 19, 20, 21, 22, 23 };
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			pattern = ANIM[ ( getActCount( ) / WAIT_ANIM_TIME ) % anim_num ];
		}
		break;
	case ACTION_MOVE:
		{
			const int ANIM[ ] = { 3, 4, 5, 6, 5, 4 };
			int anim_num = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
			pattern = ANIM[ ( getActCount( ) / WAIT_ANIM_TIME ) % anim_num ];
		}
		break;
	case ACTION_FADE_OUT:
		{
			const int ANIM[ ] = { 23, 22, 21, 20, 19, 18, 17, 16, 16 };
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
