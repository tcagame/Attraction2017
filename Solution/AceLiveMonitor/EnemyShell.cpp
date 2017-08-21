#include "EnemyShell.h"
#include "SynchronousData.h"

static const int WAIT_ANIM_TIME = 5;
static const int MAX_HP = 0;

EnemyShell::EnemyShell( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP ) {
	setRadius( 30 );
}


EnemyShell::~EnemyShell( ) {
}

void EnemyShell::act( ) {
}

void EnemyShell::setSynchronousData( unsigned char type, int camera_pos ) const {
	const int ANIM[ ] = { 166, 167, 168, 169, 170, 171, 172, 173 };
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	
	Vector pos = getPos( );
	int x = ( int )pos.x;
	int y = ( int )pos.y;

	AREA area = AREA_EVENT;
	if ( getState( ) == STATE_MAIN ) {
		x -= camera_pos;
		area = AREA_MAIN;
	}
	unsigned char attribute = 0;
	if ( getDir( ) == DIR_RIGHT ) {
		attribute |= SynchronousData::ATTRIBUTE_REVERSE;
	}
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->addObject( area, type, ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ], attribute, x, y );
}
