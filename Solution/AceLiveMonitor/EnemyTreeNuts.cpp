#include "EnemyTreeNuts.h"
#include "SynchronousData.h"
#include "Property.h"

const int WAIT_ANIM_TIME = 5;
const int FADE_IN_TIME = WAIT_ANIM_TIME * 9;

EnemyTreeNuts::EnemyTreeNuts( const Vector& pos ) :
EnemyAttack( pos, SMALL_CHAR_GRAPH_SIZE, false ),
_act( ACTION_FADE_IN ) {
	setOverlappedRadius( 18 );

	PropertyPtr property( Property::getTask( ) );
	setPower( property->getData( "TreeNuts_POWER" ) );
	setForce( property->getData( "TreeNuts_FORCE" ) );
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

void EnemyTreeNuts::setSynchronousData( int camera_pos ) const {
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
	unsigned char type = getType( );
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
