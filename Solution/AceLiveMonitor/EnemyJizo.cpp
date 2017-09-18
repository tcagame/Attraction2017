#include "EnemyJizo.h"
#include "SynchronousData.h"
#include "Property.h"

const int WAIT_ANIM_TIME = 8;
const int GRAPH_WIDTH_NUM = 16;
const int FADE_IN_TIME = WAIT_ANIM_TIME * 6;
const int MOVE_SPEED = 1;

EnemyJizo::EnemyJizo( const Vector& pos ) :
Enemy( pos, BIG_CHAR_GRAPH_SIZE ),
_act( ACTION_FADE_IN ),
_before_pos( pos ) {
	setOverlappedRadius( 48 );

	PropertyPtr property( Property::getTask( ) );
	setPower( property->getData( "Jizo_POWER" ) );
	setForce( property->getData( "Jizo_FORCE" ) );
}


EnemyJizo::~EnemyJizo( ) {
}

void EnemyJizo::act( ) {
	switch ( _act ) {
	case ACTION_FADE_IN:
		if ( getActCount( ) > FADE_IN_TIME ) {
			_act = ACTION_MOVE;
			setVec( Vector( -MOVE_SPEED, 0 ) );
		}
		break;
	case ACTION_MOVE:
		if ( _before_pos.x == getPos( ).x ) {
			if ( getDir( ) == DIR_LEFT ) {
				setVec( Vector( MOVE_SPEED, 0 ) );
			} else {
				setVec( Vector( -MOVE_SPEED, 0 ) );
			}
		}
		_before_pos = getPos( );
		break;
		}
}

void EnemyJizo::setSynchronousData( int camera_pos ) const {
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
		const int ANIM[ ] = { 0, 1, 2, 3, 4, 5, 6, 7 };
		int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
		data->addObject( area, type, ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ], attribute, x, y );
	}
		break;
	case ACTION_MOVE:
		const int ANIM[ ] = { 7, 8, 9, 10 };
		int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
		data->addObject( area, type, ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ], attribute, x, y );
		break;
	}
}
