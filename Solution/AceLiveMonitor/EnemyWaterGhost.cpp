#include "EnemyWaterGhost.h"
#include "SynchronousData.h"

static const int WAIT_ANIM_TIME = 5;
static const int MAX_HP = 0;

EnemyWaterGhost::EnemyWaterGhost( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP ) {
	setRadius( 30 );
}


EnemyWaterGhost::~EnemyWaterGhost( ) {
}

void EnemyWaterGhost::act( ) {
}

void EnemyWaterGhost::setSynchronousData( unsigned char type, int camera_pos ) const {
	const int ANIM[ ] = { 300, 301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312, 313 };
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
	data->addObject( area, type, ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ], attribute, x, y );
}
