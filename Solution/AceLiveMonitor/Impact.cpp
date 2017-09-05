#include "Impact.h"
#include "SynchronousData.h"

const int IMPACT_CHIP_SIZE = 128;
const int MAX_ANIM_COUNT = 30;

Impact::Impact( const Vector& pos, AREA area, int sprite_size ) :
_pos( pos ),
_anim_count( 0 ),
_area( area ),
_sprite_size( sprite_size ) {
}


Impact::~Impact( ) {
}

void Impact::update( ) {
	_anim_count++;
}

void Impact::setSynchronousData( int camera_pos ) const {
	int ANIM[ ] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	int pattern = ( _anim_count * anim_size ) / MAX_ANIM_COUNT;
	if ( pattern > anim_size - 1 ) {
		pattern = anim_size - 1;
	}
	int x = ( int )_pos.x;
	int y = ( int )_pos.y;

	AREA area = AREA_EVENT;
	if ( getArea( ) == AREA_STREET ) {
		x -= camera_pos;
		area = AREA_STREET;
	}
	unsigned char attribute = 0;
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->addObject( area, SynchronousData::TYPE_IMPACT, ANIM[ pattern ], attribute, x, y, _sprite_size );
}

bool Impact::isFinished( ) const {
	return ( _anim_count > MAX_ANIM_COUNT );
}

AREA Impact::getArea( ) const {
	return _area;
}
