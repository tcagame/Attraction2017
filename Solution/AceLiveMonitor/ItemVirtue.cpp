#include "ItemVirtue.h"
#include "SynchronousData.h"
#include "Family.h"

const double MOVE_SPEED = 3;
const double ACCEL_SPEED = 0.2;
const int SPEED = 1;

ItemVirtue::ItemVirtue( int target_x ) :
Item( Vector( target_x, 0 ), AREA_STREET, 32, false ),
_target( Vector( target_x, 128 - 64 ) ) {
}


ItemVirtue::~ItemVirtue( ) {
}

void ItemVirtue::act( ) {
	_target.x -= SPEED;
	
	Vector distance = _target - getPos( );
	if ( distance.getLength( ) > 1000 ) {
		_target.x = getPos( ).x;
	}
	Vector force = distance.normalize( ) * ACCEL_SPEED;
	Vector vec = ( getVec( ) + force );
	setVec( vec );
}

void ItemVirtue::setSynchronousData( int camera_pos ) const {
	Vector pos = getPos( );
	int x = ( int )pos.x;
	int y = ( int )pos.y;

	AREA area = AREA_EVENT;
	if ( getArea( ) == AREA_STREET ) {
		x -= camera_pos;
		area = AREA_STREET;
	}
	unsigned char attribute = 0;
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->addObject( area, SynchronousData::TYPE_ITEM, 34, attribute, x, y );
}
