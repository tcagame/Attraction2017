#include "EnemyGhost.h"
#include "Family.h"
#include "SynchronousData.h"
#include "Property.h"

const int WAIT_ANIM_TIME = 3;
const int FADE_IN_TIME = WAIT_ANIM_TIME * 10;
const int MOVE_SPEED = -3;
const double ASCEND_SPEED = -0.1;

EnemyGhost::EnemyGhost( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, false ),
_act( ACTION_FADE_IN ),
_ascend_speed( 0 ) {
	setOverlappedRadius( 32 );
	setVec( Vector( ) );

	PropertyPtr property( Property::getTask( ) );
	setPower( property->getData( "Ghost_POWER" ) );
	setForce( property->getData( "Ghost_FORCE" ) );
}

EnemyGhost::~EnemyGhost( ) {
}

void EnemyGhost::act( ) {
	switch ( _act ) {
	case ACTION_FADE_IN:
	{
		if ( getActCount( ) > FADE_IN_TIME ) {
			_act = ACTION_MOVE;
			setVec( Vector ( MOVE_SPEED, MOVE_SPEED / 2 ) );
		}
	}
		break;
	case ACTION_MOVE:
	{
		Vector vec = getVec( );
		int ascend_pos = Family::getTask( )->getCameraPosX( ) + 150;
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

void EnemyGhost::setSynchronousData( int camera_pos ) const {
	int anim = 0;
	switch ( _act ) {
	case ACTION_FADE_IN:
	{
		const int ANIM[ ] = { 380, 381, 382, 383, 384, 385, 386, 387, 388, 389, 390 };
		int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
		anim = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ];
	}
		break;
	case ACTION_MOVE:
	{
		const int ANIM[ ] = { 391, 392, 393, 394, 395 };
		int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
		anim = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ];
	}
		break;
	}
	
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
	data->addObject( area, type, anim, attribute, x, y );
}