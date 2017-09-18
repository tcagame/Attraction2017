#include "EnemyGama.h"
#include "SynchronousData.h"
#include "Property.h"

const int WAIT_ANIM_TIME = 5;
const int GRAPH_WIDTH_NUM = 10;
const int GUIDE_TIME = 180;

EnemyGama::EnemyGama( const Vector& pos ) :
Enemy( pos, BIG_CHAR_GRAPH_SIZE ),
_guide( false ) {
	setOverlappedRadius( 36 );

	PropertyPtr property( Property::getTask( ) );
	setPower( property->getData( "Gama_POWER" ) );
	setForce( property->getData( "Gama_FORCE" ) );
}


EnemyGama::~EnemyGama( ) {
}

void EnemyGama::act( ) {
	if ( _guide && getActCount( ) > GUIDE_TIME ) {
		damage( -1 );
	}
}

bool EnemyGama::isGuide( ) const {
	return _guide;
}

void EnemyGama::setSynchronousData( int camera_pos ) const {
	const int ANIM[ ] = {
		112, 113, 114, 115
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
	unsigned char type = getType( );
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
