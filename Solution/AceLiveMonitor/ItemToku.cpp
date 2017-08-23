#include "ItemToku.h"
#include "SynchronousData.h"

ItemToku::ItemToku( Vector pos ) :
Item( pos ) {
}


ItemToku::~ItemToku( ) {
}

void ItemToku::act( ) {
}

void ItemToku::setSynchronousData( unsigned char type, int camera_pos ) const {
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
