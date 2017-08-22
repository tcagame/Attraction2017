#include "EnemyGhost.h"
#include "Family.h"
#include "SynchronousData.h"

static const int WAIT_ANIM_TIME = 5;
static const int FADE_IN_TIME = WAIT_ANIM_TIME * 2;
static const int MAX_HP = 3;
static const int MOVE_SPEED = -3;
static const double ASCEND_SPEED = -0.1;

EnemyGhost::EnemyGhost( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP, false ),
_act( ACTION_FADE_IN ),
_ascend_speed( 0 ) {
	setRadius( 36 );
	setVec( Vector ( MOVE_SPEED, MOVE_SPEED / 2 ) );
}

EnemyGhost::~EnemyGhost( ) {
}

void EnemyGhost::act( ) {
	switch ( _act ) {
	case ACTION_FADE_IN:
		if ( getActCount( ) > FADE_IN_TIME ) {
			_act = ACTION_MOVE;
		}
		break;
	case ACTION_MOVE:
	{
		Vector vec = getVec( );
		int ascend_pos = ( int )Family::getTask( )->getCameraPos( ) + 150;
		if ( getPos( ).x < ascend_pos ) {
			vec.y += ASCEND_SPEED;
			setVec( vec );
		} else {
			setVec( vec );
		}
		break;
	}
	}
}

void EnemyGhost::setSynchronousData( unsigned char type, int camera_pos ) const {
	int anim = 0;
	switch ( _act ) {
	case ACTION_FADE_IN:
	{
		const int ANIM[ ] = { 228, 229, 230, 231, 232, 233 };
		int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
		anim = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ];
	}
		break;
	case ACTION_MOVE:
	{
		const int ANIM[ ] = { 234, 235, 236, 237, 238 };
		int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
		anim = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ];
	}
		break;
	}
	
	Vector pos = getPos( );
	int x = ( int )pos.x;
	int y = ( int )pos.y;

	AREA area = AREA_EVENT;
	if ( getState( ) == STATE_STREET ) {
		x -= camera_pos;
		area = AREA_STREET;
	}
	unsigned char attribute = 0;
	if ( getDir( ) == DIR_RIGHT ) {
		attribute |= SynchronousData::ATTRIBUTE_REVERSE;
	}
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->addObject( area, type, anim, attribute, x, y );
}