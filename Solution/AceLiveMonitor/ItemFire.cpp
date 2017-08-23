#include "ItemFire.h"
#include "SynchronousData.h"

ItemFire::ItemFire( const Vector& pos ) :
Item( pos ) {
}


ItemFire::~ItemFire( ) {
}

void ItemFire::act( ) {
}

void ItemFire::setSynchronousData( unsigned char type, int camera_pos ) const {
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
	data->addObject( area, type, 37, attribute, x, y );
}
