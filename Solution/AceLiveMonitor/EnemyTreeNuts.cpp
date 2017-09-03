#include "EnemyTreeNuts.h"
#include "SynchronousData.h"

static const int WAIT_ANIM_TIME = 5;
static const int FADE_IN_TIME = WAIT_ANIM_TIME * 9;
static const int MAX_HP = 2;

EnemyTreeNuts::EnemyTreeNuts( const Vector& pos ) :
EnemyAttack( pos, SMALL_CHAR_GRAPH_SIZE, MAX_HP, false ),
_act( ACTION_FADE_IN ) {
	setRadius( 18 );
}

EnemyTreeNuts::~EnemyTreeNuts( ) {
}

void EnemyTreeNuts::act( ) {
	switch ( _act ) {
	case ACTION_FADE_IN:
		if ( getActCount( ) > FADE_IN_TIME ) {
			_act = ACTION_MOVE;
		}
		break;
	case ACTION_MOVE:
		setVec( Vector( -5, 0 ) );
		break;
	}
}

void EnemyTreeNuts::setSynchronousData( unsigned char type, int camera_pos ) const {
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
	switch ( _act ) {
	case ACTION_FADE_IN:
	{
		const int ANIM[ ] = { 32, 33, 34, 35, 36, 37, 38, 39 };
		int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
		int idx = getActCount( ) / WAIT_ANIM_TIME;
		if ( idx >= anim_size ) {
			idx = anim_size - 1;
		}
		data->addObject( area, type, ANIM[ idx ], attribute, x, y );
	}
		break;
	case ACTION_MOVE:
	{
		const int ANIM[ ] = { 37, 38, 39, 38 };
		int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
		data->addObject( area, type, ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ], attribute, x, y );
	}
		break;
	}
}
