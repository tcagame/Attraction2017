#include "ItemVirtue.h"
#include "SynchronousData.h"

ItemVirtue::ItemVirtue( Vector pos ) :
Item( pos ) {
}


ItemVirtue::~ItemVirtue( ) {
}

void ItemVirtue::act( ) {
}

void ItemVirtue::setSynchronousData( unsigned char type, int camera_pos ) const {
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
	data->addObject( area, type, 34, attribute, x, y );
}
