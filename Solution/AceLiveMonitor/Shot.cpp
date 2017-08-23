#include "Shot.h"
#include "SynchronousData.h"

static const int SHOT_SPEED = 10; 
static const int VANISH_LENGTH = 500;
static const int MAX_HP = 3;

Shot::Shot( const Vector& pos, DIR dir, int power ) :
Character( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP, false ),
_dir( dir ),
_pos( pos ),
_power( power ) {
	Vector vec = Vector( SHOT_SPEED, 0 );
	if ( dir == DIR_LEFT ) {
		vec.x *= -1;
	}
	setVec( vec );
	setRadius( 20 );
}

Shot::~Shot( ) {
}

void Shot::act( ) {
	if ( getActCount( ) * getVec( ).getLength( ) > VANISH_LENGTH ) {
		setFinished( );
	}
}

DIR Shot::getDir( ) const {
	return _dir;
}

int Shot::getPower( ) const {
	return _power;
}

void Shot::setSynchronousData( unsigned char type, int camera_pos ) const {
	int ANIM[ ] = { 16, 17, 18, 19, 20, 21, 22, 23 };
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
	data->addObject( area, type, ANIM[ ( _power - 1 ) * 2 + ( getActCount( ) % 2 ) ], attribute, x, y );
}
