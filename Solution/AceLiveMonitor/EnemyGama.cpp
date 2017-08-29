#include "EnemyGama.h"
#include "SynchronousData.h"

static const int WAIT_ANIM_TIME = 5;
static const int GRAPH_WIDTH_NUM = 10;
static const int MAX_HP = 6;
static const int GUIDE_TIME = 180;

EnemyGama::EnemyGama( const Vector& pos ) :
Enemy( pos, BIG_CHAR_GRAPH_SIZE, MAX_HP ),
_guide( false ) {
	setRadius( 36 );
}


EnemyGama::~EnemyGama( ) {
}

void EnemyGama::act( ) {
	if ( _guide && getActCount( ) > GUIDE_TIME ) {
		setFinished( );
	}
}

bool EnemyGama::isGuide( ) const {
	return _guide;
}

void EnemyGama::setSynchronousData( unsigned char type, int camera_pos ) const {
	const int ANIM[ ] = {
		60, 61, 62, 63, 62, 61
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	int pattern = ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ];
	if ( _guide ) {
		pattern += 4;
	}
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
	data->addObject( area, type, pattern, attribute, x, y );
}

void EnemyGama::damage( int force ) {
	if ( force < 0 ) {
		Enemy::damage( force );
	}

	if ( _guide ) {
		return;
	}

	if ( getPower( ) - force > 1 ) {
		Enemy::damage( force );
	} else {
		_guide = true;
		setActCount( 0 );
		setForce( 0 );
	}
}
