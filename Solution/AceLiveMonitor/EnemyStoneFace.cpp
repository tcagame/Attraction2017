#include "EnemyStoneFace.h"
#include "Family.h"
#include "SynchronousData.h"
#include "Property.h"

const int WAIT_ANIM_TIME = 5;
const double MAX_MOVE_SPEED = 5;
const double ACCEL = 0.3;

EnemyStoneFace::EnemyStoneFace( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, false ),
_action( ACTION_IN ) {
	Vector target = Vector( Family::getTask( )->getCameraPosX( ) + SCREEN_WIDTH / 2, GRAPH_SIZE );
	Vector vec = target - getPos( );
	if ( fabs( vec.x ) < fabs( vec.y ) ) {
		vec.y *= 0.5;
	}
	vec = vec.normalize( ) * MAX_MOVE_SPEED;
	setVec( vec );

	PropertyPtr property( Property::getTask( ) );
	setPower( property->getData( "StoneFace_POWER" ) );
	setForce( property->getData( "StoneFace_FORCE" ) );
	setOverlappedRadius( property->getData( "StoneFace_RADIUS" ) );
}

EnemyStoneFace::~EnemyStoneFace( ) {
}

void EnemyStoneFace::act( ) {
	Vector vec = getVec( );
	switch ( _action ) {
	case ACTION_IN:
			_action = ACTION_MOVE;
		if ( getPos( ).y > GRAPH_SIZE / 2 ) {
		}
	break;
	case ACTION_MOVE:
	{
		Vector target = Vector( Family::getTask( )->getCameraPosX( ) + SCREEN_WIDTH / 2, GRAPH_SIZE / 2 + getChipSize( ) );
		double angle = fmod( ( double )getActCount( ) * PI * 0.01, PI * 2 );
		Vector add = Vector( sin( angle ) * 150, sin( angle * 2 ) * 40 );
		target += add;
		Vector pos = getPos( );
		Vector distance = target - pos;
		vec += distance.normalize( ) * ACCEL;
		if ( vec.getLength2( ) > MAX_MOVE_SPEED * MAX_MOVE_SPEED ) {
			vec = vec.normalize( ) * MAX_MOVE_SPEED;
		}
		if ( pos.y + vec.y > GRAPH_SIZE ) {
			vec.y = GRAPH_SIZE - pos.y - 0.1;
		}
	}
	break;
	}
	setVec( vec );
}

void EnemyStoneFace::setSynchronousData( int camera_pos ) const {
	const int ANIM[ ] = {
		32, 33, 34, 35, 36
	};
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
	if ( getDir( ) == DIR_RIGHT ) {
		attribute |= SynchronousData::ATTRIBUTE_REVERSE;
	}
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	unsigned char type = getType( );
	data->addObject( area, type, ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ], attribute, x, y );
}

Vector EnemyStoneFace::getOverlappedPos( ) const {
	return Character::getOverlappedPos( ) + Vector( 0, -10 );
}