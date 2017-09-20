#include "EnemyFaceAndHand.h"
#include "SynchronousData.h"
#include "Property.h"

const int WAIT_ANIM_TIME = 6;
const int FADE_IN_TIME = 15;

EnemyFaceAndHand::EnemyFaceAndHand( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, false ),
_act( ACTION_FADE_IN ){

	PropertyPtr property( Property::getTask( ) );
	setPower( property->getData( "FaceAndHand_POWER" ) );
	setForce( property->getData( "FaceAndHand_FORCE" ) );
}


EnemyFaceAndHand::~EnemyFaceAndHand( ) {
}

void EnemyFaceAndHand::act( ) {
	switch ( _act ) {
	case ACTION_FADE_IN:
		if ( getActCount( ) > FADE_IN_TIME ) {
			_act = ACTION_MOVE;
		}
		break;
	case ACTION_MOVE:
		setVec( Vector( -3, 1 ) );
		break;
	}
}

void EnemyFaceAndHand::setSynchronousData( int camera_pos ) const {	
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
		const int ANIM[ ] = { 200, 201, 202 };
		int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
		data->addObject( area, type, ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ], attribute, x, y );
	}
		break;
	case ACTION_MOVE:
	{
		const int ANIM[ ] = { 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214 };
		int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
		data->addObject( area, type, ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ], attribute, x, y );
	}
		break;
	}
}
