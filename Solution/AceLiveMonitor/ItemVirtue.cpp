#include "ItemVirtue.h"
#include "SynchronousData.h"
#include "Family.h"

const double MOVE_SPEED = 3;
const double ACCEL_SPEED = 1.5;

ItemVirtue::ItemVirtue( Vector pos ) :
Item( pos, 32, false ),
_target( Vector( pos.x, 128 ) ) {
}


ItemVirtue::~ItemVirtue( ) {
}

void ItemVirtue::act( ) {
	/*
	Vector distance = _target - getPos( );
	Vector force = distance.normalize( ) * ACCEL_SPEED;
	Vector vec = ( getVec( ) + force ).normalize( ) * MOVE_SPEED;
	setVec( vec );
	*/
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
