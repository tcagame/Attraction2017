#include "EnemyGama.h"
#include "SynchronousData.h"

static const int WAIT_ANIM_TIME = 5;
static const int GRAPH_WIDTH_NUM = 10;
static const int MAX_HP = 6;

EnemyGama::EnemyGama( const Vector& pos ) :
Enemy( pos, BIG_CHAR_GRAPH_SIZE, MAX_HP ) {
	setRadius( 48 );
}


EnemyGama::~EnemyGama( ) {
}

void EnemyGama::act( ) {
}

void EnemyGama::setSynchronousData( unsigned char type, int camera_pos ) const {
	const int ANIM[ ] = {
		60, 61, 62, 63, 62, 61
	};
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

Chip EnemyGama::getChip( ) const {
	return Chip( );
}
