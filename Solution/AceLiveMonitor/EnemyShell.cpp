#include "EnemyShell.h"
#include "SynchronousData.h"
#include "Property.h"

const int WAIT_ANIM_TIME = 5;

EnemyShell::EnemyShell( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE ) {
	setOverlappedRadius( 30 );

	PropertyPtr property( Property::getTask( ) );
	setPower( property->getData( "Shell_POWER" ) );
	setForce( property->getData( "Shell_FORCE" ) );
}


EnemyShell::~EnemyShell( ) {
}

void EnemyShell::act( ) {
}

void EnemyShell::setSynchronousData( int camera_pos ) const {
	const int ANIM[ ] = { 189, 190, 191, 192, 193, 194, 195, 196, 197 };
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
