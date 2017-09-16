#include "EnemyMoth.h"
#include "SynchronousData.h"

static const int WAIT_ANIM_TIME = 5;
static const int FLOAT_RANGE = 4;
static const int MAX_HP = 2;

EnemyMoth::EnemyMoth( const Vector& pos ) :
Enemy( pos, SMALL_CHAR_GRAPH_SIZE, MAX_HP, false ),
_vy( 0 ),
_dir( 1 ) {
	setOverlappedRadius( 16 );
}


EnemyMoth::~EnemyMoth( ) {
}

void EnemyMoth::act( ) {
	_vy += _dir;
	setVec( Vector( 0, _vy ) );

	if ( _vy < -FLOAT_RANGE ) {
		_dir = 1;
	}
	if ( _vy > FLOAT_RANGE ) {
		_dir = -1;
	}
}

void EnemyMoth::setSynchronousData( int camera_pos ) const {
	int ANIM[ ] = { 40, 41, 42, 43 };
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
