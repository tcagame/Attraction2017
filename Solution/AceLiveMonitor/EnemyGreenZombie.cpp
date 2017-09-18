#include "EnemyGreenZombie.h"
#include "SynchronousData.h"
#include "Property.h"

const int WAIT_ANIM_TIME = 5;
const int MOVE_SPEED = -5;
const int JUMP_POWER = -10;

EnemyGreenZombie::EnemyGreenZombie( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE ),
_before_pos( Vector( ) ) {
	setVec( Vector( MOVE_SPEED, 0 ) );
	setOverlappedRadius( 36 );

	PropertyPtr property( Property::getTask( ) );
	setPower( property->getData( "GreenZombie_POWER" ) );
	setForce( property->getData( "GreenZombie_FORCE" ) );
}


EnemyGreenZombie::~EnemyGreenZombie( ) {
}

void EnemyGreenZombie::act( ) {
	if ( _before_pos.x == getPos( ).x ) {
		Vector vec( getVec( ) );
		vec.x *= -1;
		setVec( vec );
	}
	if ( isStanding( ) && getActCount( ) % 30 == 0 ) {
		Vector vec( getVec( ) );
		vec.y = JUMP_POWER;
		setVec( vec );
	}
	_before_pos = getPos( );
}

void EnemyGreenZombie::setSynchronousData( int camera_pos ) const {
	const int ANIM[ ] = {
		66, 67, 68, 69, 70, 71
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
