#include "EnemyWhiteMist.h"
#include "SynchronousData.h"

static const int WAIT_ANIM_TIME = 5;
static const int MOVE_SPEED = 2;
static const int FLOAT_RANGE = 10;
static const int MAX_HP = 3;

EnemyWhiteMist::EnemyWhiteMist( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP, false ),
_vy( 0 ),
_dir( 1 ) {
	setOverlappedRadius( 36 );
}


EnemyWhiteMist::~EnemyWhiteMist( ) {
}

void EnemyWhiteMist::act( ) {
	_vy += _dir;
	setVec( Vector( -MOVE_SPEED, _vy ) );

	if ( _vy < -FLOAT_RANGE ) {
		_dir = 1;
	}
	if ( _vy > FLOAT_RANGE ) {
		_dir = -1;
	}
}

void EnemyWhiteMist::setSynchronousData( int camera_pos ) const {
	const int ANIM[ ] = {
		160, 161, 162, 163, 164, 165, 166, 167, 168, 169
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
