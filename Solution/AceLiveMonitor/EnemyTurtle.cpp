#include "EnemyTurtle.h"
#include "SynchronousData.h"

const int WAIT_ANIM_TIME = 10;

EnemyTurtle::EnemyTurtle( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE ) {
	setPower( 999 );
}


EnemyTurtle::~EnemyTurtle( ) {
}

void EnemyTurtle::act( ) {
	int a = 0;
}

void EnemyTurtle::setSynchronousData( int camera_pos ) const {
	const int ANIM[ ] = {
		24, 25, 26, 27, 28
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
	data->addObject( area, SynchronousData::TYPE_RYUGU, ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ], attribute, x, y, 64 );
}
