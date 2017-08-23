#include "ItemRock.h"
#include "SynchronousData.h"

ItemRock::ItemRock( const Vector& pos ) :
Item( pos ) {
}


ItemRock::~ItemRock( ) {
}

void ItemRock::act( ) {
}

void ItemRock::setSynchronousData( unsigned char type, int camera_pos ) const {
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
	data->addObject( area, type, 38, attribute, x, y );
}
