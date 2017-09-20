#include "EnemyRedBirdAttack.h"
#include "SynchronousData.h"
#include "Property.h"

const int WAIT_ANIM_TIME = 2;

EnemyRedBirdAttack::EnemyRedBirdAttack( const Vector& pos ) :
EnemyAttack( pos, SMALL_CHAR_GRAPH_SIZE ) {
	setOverlappedRadius( 18 );

	PropertyPtr property( Property::getTask( ) );
	setPower( property->getData( "RedBirdAttack_POWER" ) );
	setForce( property->getData( "RedBirdAttack_FORCE" ) );
}


EnemyRedBirdAttack::~EnemyRedBirdAttack( ) {
}

void EnemyRedBirdAttack::act( ) {
	if ( isStanding( ) ) damage( -1 );
}

void EnemyRedBirdAttack::setSynchronousData( int camera_pos ) const {
	const int ANIM[ ] = {
		8, 9, 10, 11, 12, 13, 14, 15
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
